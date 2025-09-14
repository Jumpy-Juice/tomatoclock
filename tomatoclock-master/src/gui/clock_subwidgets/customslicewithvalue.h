#ifndef CUSTOMSLICEWITHVALUE_H
#define CUSTOMSLICEWITHVALUE_H

#include <QObject>
#include <QtCharts/QPieSlice>
#include <QString>

    class CustomSliceWithValue : public QPieSlice {
    Q_OBJECT

private:
    QString name_;

public:
    // 直接在头文件中实现
    CustomSliceWithValue(const QString& label = QString(), qreal value = 0.0, QObject* parent = nullptr)
        : QPieSlice(label, value, parent), name_(label) {
        // 构造函数实现
    }

    void setName(const QString& name) {
        name_ = name;
        setLabel(name);
    }

    QString name() const {
        return name_;
    }

public slots:
    void onClicked() {
        setExploded(!isExploded());
    }

    void onHovered(bool state) {
        Q_UNUSED(state)
        // 简单的悬停处理
    }
};

#endif  // CUSTOMSLICEWITHVALUE_H
