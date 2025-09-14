#include "../../tc/tc/tomatoclocktimer.h"
#include "../../tc/tc/settingfileoperations.h"
#include <QDebug>

namespace lon {

TomatoClockTimer::TomatoClockTimer(QObject* parent)
    : QObject(parent), running_(false), display_clock_(nullptr), timer_(new QTimer(this)) {
    timer_->setInterval(1000);
    timer_->start();

    auto clockOptions =
        std::make_unique<ClockOptions>(SettingFileOperations().readClockOptionFromFile());
    timer_status_ = std::make_unique<TimerStatus>(std::move(clockOptions));

    connect(timer_.get(), &QTimer::timeout, this, &TomatoClockTimer::oneSecondPassed);
}

void TomatoClockTimer::setDisplayClock(DisplayClockBase* display_clock) {
    display_clock_ = display_clock;
}


void TomatoClockTimer::updateSettings() {
    if (running_) {
        qDebug() << "计时器正在运行，设置将在下次启动时生效";
        return;
    }
    
    // 从文件重新加载设置
    auto newClockOptions = 
        std::make_unique<ClockOptions>(SettingFileOperations().readClockOptionFromFile());
    
    // 创建新的计时器状态
    timer_status_ = std::make_unique<TimerStatus>(std::move(newClockOptions));
    
    qDebug() << "计时器设置已更新";
}

void TomatoClockTimer::oneSecondPassed() {
    if (!running_)
        return;

    bool finished = timer_status_->subOneSecond();

    if (finished) {
        stop();
        emit tomatoFinished();
        return;
    }

    qDebug("Time left: %d : %d",
           timer_status_->timeleft()->minutes(),
           timer_status_->timeleft()->seconds());

    if (display_clock_)
        display_clock_->updateTimeDisplay(timer_status_.get());
}

}  // namespace lon

