#include "../../tc/tc/settingfileoperations.h"
#include "../../tc/tc/clockoptions.hpp"
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <fstream>

SettingFileOperations::SettingFileOperations() {}

void SettingFileOperations::saveClockOptionToFile(const lon::ClockOptions& option) {
    QJsonObject clock_page;
    clock_page.insert("WorkTime", option.workTime()->minutes_);
    clock_page.insert("ShortbreakTime", option.shortBreakTime()->minutes_);
    clock_page.insert("LongbreakTime", option.longBreakTime()->minutes_);
    clock_page.insert("TimesBetweenLong", option.shortBreaksBeforeLong());
    clock_page.insert("KeepWorking", static_cast<int8_t>(option.keepWorking()));

    QJsonObject json;
    json.insert("ClockSetting", QJsonValue(clock_page));

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Indented);

    // 确保user目录存在
    QString dirPath = "user";
    QDir dir;
    if (!dir.exists(dirPath)) {
        dir.mkpath(dirPath);
    }

    std::string filename = "user/setting.json";
    std::ofstream setting_file(filename, std::ios::binary);
    if (setting_file.is_open()) {
        setting_file.write(byteArray.data(), byteArray.size());
        setting_file.close();
        qDebug() << "设置已保存到:" << QString::fromStdString(filename);
    } else {
        qDebug() << "无法保存设置文件:" << QString::fromStdString(filename);
    }
}


lon::ClockOptions SettingFileOperations::readClockOptionFromFile() {
    int8_t work = 25, shortbreak = 5, longbreak = 15, shortbreak_times = 3, keep_working = 0;
    QFile  file_("user/setting.json");
    if (!file_.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file in " << __FILE__ << __LINE__;
        return lon::ClockOptions(work,
                                 0,
                                 shortbreak,
                                 0,
                                 longbreak,
                                 0,
                                 shortbreak_times,
                                 static_cast<bool>(keep_working));
    }
    QTextStream in(&file_);
    QString     in_string = in.readAll();

    QJsonParseError error;
    QJsonDocument   json_document = QJsonDocument::fromJson(in_string.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (!(json_document.isNull() || json_document.isEmpty()) && json_document.isObject()) {
            QVariantMap data = json_document.toVariant().toMap();
            if (!data[QLatin1String("errorCode")].toInt()) {
                QVariantMap clock_settings;
                if (data.contains(QLatin1String("ClockSetting")))
                    clock_settings = data[QLatin1String("ClockSetting")].toMap();
                if (clock_settings.contains(QLatin1String("WorkTime")))
                    work = clock_settings[QLatin1String("WorkTime")].toInt();
                if (clock_settings.contains(QLatin1String("ShortbreakTime")))
                    shortbreak = clock_settings[QLatin1String("ShortbreakTime")].toInt();
                if (clock_settings.contains(QLatin1String("LongbreakTime")))
                    longbreak = clock_settings[QLatin1String("LongbreakTime")].toInt();
                if (clock_settings.contains(QLatin1String("TimesBetweenLong")))
                    shortbreak_times = clock_settings[QLatin1String("TimesBetweenLong")].toInt();
                if (clock_settings.contains(QLatin1String("KeepWorking")))
                    keep_working = clock_settings[QLatin1String("KeepWorking")].toInt();
            }
        }
    } else {
        qDebug() << "Error String : " << error.errorString();
    }
    file_.close();
    return lon::ClockOptions(
        work, 0, shortbreak, 0, longbreak, 0, shortbreak_times, static_cast<bool>(keep_working));
}
