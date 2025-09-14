#pragma once

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <list>
#include <vector>
#include <cstdint>

#include "DataStructure.hpp"

namespace lon {

class ClockSql {
private:
    QSqlDatabase sql_;
    QSqlQuery    query_;

    ClockSql() {
        sql_ = QSqlDatabase::addDatabase("QSQLITE");
        sql_.setDatabaseName("ClockSql.db");

        if (!sql_.open()) {
            throw std::logic_error("Database cannot be opened");
        }
        query_ = QSqlQuery(sql_);
        initTables();
    }

    void initTables() {
        query_.exec("CREATE TABLE IF NOT EXISTS labels (LabelName TEXT PRIMARY KEY)");
        query_.exec(
            "CREATE TABLE IF NOT EXISTS targets (TargetId INTEGER PRIMARY KEY, TargetName TEXT "
            "UNIQUE, LabelName TEXT REFERENCES labels(LabelName))");
        query_.exec(
            "CREATE TABLE IF NOT EXISTS finishedtomato (TomatoId INTEGER PRIMARY KEY, TargetId "
            "INTEGER REFERENCES targets(TargetId), DuringTime INTEGER, FinishTime DATETIME)");
    }

    void fillTimeData(std::array<uint16_t, 31>& arr, const QString& queryStr) {
        query_.exec(queryStr);
        while (query_.next()) {
            int idx = query_.value(0).toInt();
            if (idx >= 0 && idx < static_cast<int>(arr.size())) {
                arr[idx] = static_cast<uint16_t>(query_.value(1).toInt());
            }
        }
    }

    void fillPairData(std::vector<std::pair<QString, int>>& vec, const QString& queryStr) {
        query_.exec(queryStr);
        while (query_.next()) {
            vec.emplace_back(query_.value(0).toString(), query_.value(1).toInt());
        }
    }

public:
    static ClockSql* instance() {
        static ClockSql instance_;
        return &instance_;
    }

    bool addAFinishedTomato(uint8_t duringtime, const QString& label, const QString& target) {
        // 首先检查目标是否存在
        if (!targetExists(label, target)) {
            qDebug() << "错误：目标不存在 - 标签:" << label << ", 目标:" << target;
            // 尝试自动创建目标
            addTarget(label, target);
            qDebug() << "已自动创建目标:" << target << " (标签:" << label << ")";
        }
        
        // 获取TargetId
        query_.prepare("SELECT TargetId FROM targets WHERE TargetName = :target AND LabelName = :label");
        query_.bindValue(":target", target);
        query_.bindValue(":label", label);
        
        if (!query_.exec()) {
            qDebug() << "数据库查询错误:" << query_.lastError().text();
            return false;
        }
        
        if (!query_.next()) {
            qDebug() << "错误：找不到目标ID - 标签:" << label << ", 目标:" << target;
            return false;
        }
        
        int targetId = query_.value(0).toInt();
        
        // 插入完成的番茄钟记录
        query_.prepare(R"(
            INSERT INTO finishedtomato(TomatoId, TargetId, DuringTime, FinishTime)
            SELECT IFNULL(MAX(TomatoId), 0) + 1, :targetId, :during, datetime('now', 'localtime')
            FROM finishedtomato
        )");
        query_.bindValue(":targetId", targetId);
        query_.bindValue(":during", duringtime);
        
        if (!query_.exec()) {
            qDebug() << "插入番茄钟记录失败:" << query_.lastError().text();
            return false;
        }
        
        qDebug() << "成功记录番茄钟: " << duringtime << "分钟";
        return true;
    }

    bool addLabel(const QString& label) {
        query_.prepare("INSERT OR IGNORE INTO labels VALUES (:label)");
        query_.bindValue(":label", label);
        if (!query_.exec()) {
            qDebug() << "添加标签失败:" << query_.lastError().text();
            return false;
        }
        return true;
    }

    void deleteLabel(const QString& label) {
        query_.prepare("DELETE FROM labels WHERE LabelName = :label");
        query_.bindValue(":label", label);
        bool success = query_.exec();
        
        if (success) {
            int affected = query_.numRowsAffected();
            qDebug() << "删除标签成功，标签名：" << label << "，影响行数：" << affected;
        } else {
            qDebug() << "删除标签失败，标签名：" << label << "，错误：" << query_.lastError().text();
        }
    }

    bool addTarget(const QString& label, const QString& target) {
        // 首先确保标签存在
        addLabel(label);
        
        query_.prepare(R"(
            INSERT INTO targets(TargetId, TargetName, LabelName)
            SELECT IFNULL(MAX(TargetId), 0) + 1, :target, :label FROM targets
        )");
        query_.bindValue(":label", label);
        query_.bindValue(":target", target);
        
        if (!query_.exec()) {
            qDebug() << "添加目标失败:" << query_.lastError().text();
            return false;
        }
        return true;
    }

    void deleteTarget(const QString& target) {
        query_.prepare("DELETE FROM targets WHERE TargetName = :target");
        query_.bindValue(":target", target);
        bool success = query_.exec();
        
        if (success) {
            int affected = query_.numRowsAffected();
            qDebug() << "删除目标成功，目标名：" << target << "，影响行数：" << affected;
        } else {
            qDebug() << "删除目标失败，目标名：" << target << "，错误：" << query_.lastError().text();
        }
    }

    void deleteTargetsByLabel(const QString& label) {
        query_.prepare("DELETE FROM targets WHERE LabelName = :label");
        query_.bindValue(":label", label);
        bool success = query_.exec();
        
        if (success) {
            int affected = query_.numRowsAffected();
            qDebug() << "删除标签下所有目标成功，标签名：" << label << "，影响行数：" << affected;
        } else {
            qDebug() << "删除标签下所有目标失败，标签名：" << label << "，错误：" << query_.lastError().text();
        }
    }

    // 直接在类中实现这些函数
    lon::tomato_clock::TodayData getTodayData() {
        lon::tomato_clock::TodayData data;

        // 获取今天按小时统计的番茄钟数量
        query_.exec(R"(
            SELECT strftime('%H', FinishTime) as hour, COUNT(*), SUM(DuringTime)
            FROM finishedtomato
            WHERE DATE(FinishTime) = DATE('now', 'localtime')
            GROUP BY hour
            ORDER BY hour
        )");

        while (query_.next()) {
            int hour = query_.value(0).toInt();
            if (hour >= 0 && hour < 24) {
                data.time_data_p[hour] = static_cast<uint16_t>(query_.value(1).toInt());
                data.total_time_p[hour] = static_cast<uint16_t>(query_.value(2).toInt());
            }
        }

        // 获取今天的目标数据
        fillPairData(data.target_data, R"(
            SELECT t.TargetName, COUNT(*)
            FROM finishedtomato f
            JOIN targets t ON f.TargetId = t.TargetId
            WHERE DATE(f.FinishTime) = DATE('now', 'localtime')
            GROUP BY t.TargetName
            ORDER BY COUNT(*) DESC
        )");

        // 获取今天的标签数据
        fillPairData(data.label_data, R"(
            SELECT t.LabelName, COUNT(*)
            FROM finishedtomato f
            JOIN targets t ON f.TargetId = t.TargetId
            WHERE DATE(f.FinishTime) = DATE('now', 'localtime')
            GROUP BY t.LabelName
            ORDER BY COUNT(*) DESC
        )");

        return data;
    }

    lon::tomato_clock::LastWeekData getLastWeekData() {
        lon::tomato_clock::LastWeekData data;

        // 获取过去7天的数据
        query_.exec(R"(
            SELECT strftime('%w', FinishTime) as day_of_week, COUNT(*), SUM(DuringTime)
            FROM finishedtomato
            WHERE DATE(FinishTime) >= DATE('now', 'localtime', '-7 days')
            GROUP BY day_of_week
            ORDER BY day_of_week
        )");

        while (query_.next()) {
            int idx = query_.value(0).toInt();
            if (idx >= 0 && idx < 7) {
                data.time_data_p[idx] = static_cast<uint16_t>(query_.value(1).toInt());
                data.total_time_p[idx] = static_cast<uint16_t>(query_.value(2).toInt());
            }
        }

        // 获取过去一周的目标数据
        fillPairData(data.target_data, R"(
            SELECT t.TargetName, COUNT(*)
            FROM finishedtomato f
            JOIN targets t ON f.TargetId = t.TargetId
            WHERE DATE(f.FinishTime) >= DATE('now', 'localtime', '-7 days')
            GROUP BY t.TargetName
            ORDER BY COUNT(*) DESC
        )");

        // 获取过去一周的标签数据
        fillPairData(data.label_data, R"(
            SELECT t.LabelName, COUNT(*)
            FROM finishedtomato f
            JOIN targets t ON f.TargetId = t.TargetId
            WHERE DATE(f.FinishTime) >= DATE('now', 'localtime', '-7 days')
            GROUP BY t.LabelName
            ORDER BY COUNT(*) DESC
        )");

        return data;
    }

    lon::tomato_clock::LastMonthData getLastMonthData() {
        lon::tomato_clock::LastMonthData data;

        // 获取过去30天的数据
        query_.exec(R"(
            SELECT strftime('%d', FinishTime) as day_of_month, COUNT(*), SUM(DuringTime)
            FROM finishedtomato
            WHERE DATE(FinishTime) >= DATE('now', 'localtime', '-30 days')
            GROUP BY day_of_month
            ORDER BY day_of_month
        )");

        while (query_.next()) {
            int idx = query_.value(0).toInt() - 1; // 数组从0开始
            if (idx >= 0 && idx < 31) {
                data.time_data_p[idx] = static_cast<uint16_t>(query_.value(1).toInt());
                data.total_time_p[idx] = static_cast<uint16_t>(query_.value(2).toInt());
            }
        }

        // 获取过去一个月的目标数据
        fillPairData(data.target_data, R"(
            SELECT t.TargetName, COUNT(*)
            FROM finishedtomato f
            JOIN targets t ON f.TargetId = t.TargetId
            WHERE DATE(f.FinishTime) >= DATE('now', 'localtime', '-30 days')
            GROUP BY t.TargetName
            ORDER BY COUNT(*) DESC
        )");

        // 获取过去一个月的标签数据
        fillPairData(data.label_data, R"(
            SELECT t.LabelName, COUNT(*)
            FROM finishedtomato f
            JOIN targets t ON f.TargetId = t.TargetId
            WHERE DATE(f.FinishTime) >= DATE('now', 'localtime', '-30 days')
            GROUP BY t.LabelName
            ORDER BY COUNT(*) DESC
        )");

        return data;
    }

    std::vector<QString> getLastYearData() {
        std::vector<QString> data;
        query_.exec(R"(
            SELECT strftime('%Y-%m', FinishTime) as month, COUNT(*), SUM(DuringTime)
            FROM finishedtomato
            WHERE DATE(FinishTime) >= DATE('now', 'localtime', '-1 year')
            GROUP BY month
            ORDER BY month
        )");

        while (query_.next()) {
            QString monthData = QString("%1: %2个番茄钟, %3分钟")
                                    .arg(query_.value(0).toString())
                                    .arg(query_.value(1).toInt())
                                    .arg(query_.value(2).toInt());
            data.push_back(monthData);
        }
        return data;
    }

    std::vector<int> getBestWorkTimeDesc(const QString& duration) {
        std::vector<int> data;
        query_.prepare(R"(
            SELECT strftime('%H', FinishTime) as hour, COUNT(*)
            FROM finishedtomato
            WHERE DuringTime = :duration
            GROUP BY hour
            ORDER BY COUNT(*) DESC
            LIMIT 10
        )");
        query_.bindValue(":duration", duration);
        query_.exec();

        while (query_.next()) {
            data.push_back(query_.value(0).toInt());
        }
        return data;
    }

    std::list<QString> getAllLabels() {
        std::list<QString> labels;
        query_.exec("SELECT LabelName FROM labels ORDER BY LabelName");

        while (query_.next()) {
            labels.push_back(query_.value(0).toString());
        }
        return labels;
    }

    std::vector<QString> getTargetsByLabel(const QString& label) {
        std::vector<QString> targets;
        query_.prepare("SELECT TargetName FROM targets WHERE LabelName = :label ORDER BY TargetName");
        query_.bindValue(":label", label);
        query_.exec();

        while (query_.next()) {
            targets.push_back(query_.value(0).toString());
        }
        return targets;
    }

    std::list<std::pair<QString, QString>> getAllTargetsAndLabels() {
        std::list<std::pair<QString, QString>> data;
        query_.exec("SELECT TargetName, LabelName FROM targets ORDER BY LabelName, TargetName");

        while (query_.next()) {
            data.emplace_back(query_.value(0).toString(), query_.value(1).toString());
        }
        return data;
    }

    bool targetExists(const QString& label, const QString& target) {
        query_.prepare("SELECT COUNT(*) FROM targets WHERE LabelName = :label AND TargetName = :target");
        query_.bindValue(":label", label);
        query_.bindValue(":target", target);
        query_.exec();

        if (query_.next()) {
            return query_.value(0).toInt() > 0;
        }
        return false;
    }
};

}  // namespace lon
