#ifndef TOMATOCLOCKTIMER_H
#define TOMATOCLOCKTIMER_H

#include <QObject>
#include <QTimer>
#include <memory>

#include "TimeStatus.hpp"
#include "displayclockbase.h"

namespace lon {


class TomatoClockTimer : public QObject {
    Q_OBJECT

public:
    explicit TomatoClockTimer(QObject* parent = nullptr);

    void setDisplayClock(DisplayClockBase* display_clock);

    void start() {
        running_ = true;
    }
    void stop() {
        running_ = false;
    }
    void clear() {
        timer_status_->clear();
    }

    const TimerStatus& timerStatus() const {
        return *timer_status_;
    }

    /// <summary>
    /// 更新计时器设置，从设置文件重新加载配置
    /// </summary>
    void updateSettings();

    void clearRunning();

signals:
    void tomatoFinished();

private slots:
    void oneSecondPassed();

private:
    bool running_ = false;

    std::unique_ptr<TimerStatus> timer_status_;             // owned
    std::unique_ptr<QTimer>      timer_;                    // owned
    DisplayClockBase*            display_clock_ = nullptr;  // not owned
};

}  // namespace lon

#endif  // TOMATOCLOCKTIMER_H
