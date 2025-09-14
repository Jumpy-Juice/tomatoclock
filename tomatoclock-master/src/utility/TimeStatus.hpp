#ifndef TIMESTATUS_H
#define TIMESTATUS_H

#include <QDebug>
#include <memory>
#include <stdexcept>

#include "clockoptions.hpp"

namespace lon {

class TimeLeft : public ClockTime {
public:
    TimeLeft() : ClockTime(0, 0) {}
    TimeLeft(int8_t minutes, int8_t seconds) : ClockTime(minutes, seconds) {}

    void clear() {
        minutes_ = 0;
        seconds_ = 0;
    }

    int8_t subOneSecond() {
        if (minutes_ == 0 && seconds_ == 0)
            return -1;
        if (seconds_ == 0) {
            --minutes_;
            seconds_ = 59;
        } else {
            --seconds_;
        }
        return (minutes_ == 0 && seconds_ == 0) ? 0 : 1;
    }

    int8_t minutes() const {
        return minutes_;
    }
    int8_t seconds() const {
        return seconds_;
    }

    void setMinutes(int8_t m) {
        minutes_ = m;
    }
    void setSeconds(int8_t s) {
        seconds_ = s;
    }
};

class TimerStatus {
public:
    enum class NextStatus : int8_t { Working, ShortBreak, LongBreak };

    explicit TimerStatus(std::unique_ptr<ClockOptions> options)
        : is_break_(false),
          short_break_times_(0),
          clock_options_(std::move(options)),
          timeleft_(std::make_unique<TimeLeft>()) {
        setTimeFrom(clock_options_->workTime());
        total_time_ = clock_options_->workTime();
    }

    bool subOneSecond() {
        int8_t result = timeleft_->subOneSecond();

        if (result == -1) {
            throw std::logic_error("Timer underflow: negative time.");
        }

        if (result == 0) {
            switch (getNextStatus()) {
                case NextStatus::Working:
                    setTimeFrom(clock_options_->workTime());
                    total_time_ = clock_options_->workTime();
                    is_break_ = false;
                    return true;

                case NextStatus::ShortBreak:
                    setTimeFrom(clock_options_->shortBreakTime());
                    total_time_ = clock_options_->shortBreakTime();
                    ++short_break_times_;
                    is_break_ = true;
                    break;

                case NextStatus::LongBreak:
                    setTimeFrom(clock_options_->longBreakTime());
                    total_time_ = clock_options_->longBreakTime();
                    short_break_times_ = 0;
                    is_break_ = true;
                    break;
            }
        }

        return false;
    }

    void clear() {
        timeleft_->clear();
    }

    const TimeLeft* timeleft() const {
        return timeleft_.get();
    }

    bool isBreak() const {
        return is_break_;
    }

    int8_t shortBreakCount() const {
        return short_break_times_;
    }

    const std::unique_ptr<ClockOptions>& options() const {
        return clock_options_;
    }

    const ClockTime* currentStageTotalTime() const {
        return total_time_;
    }

private:
    bool                          is_break_;
    int8_t                        short_break_times_;
    std::unique_ptr<TimeLeft>     timeleft_;
    const ClockTime*              total_time_ = nullptr;
    std::unique_ptr<ClockOptions> clock_options_;

    void setTimeFrom(const ClockTime* src) {
        timeleft_->setMinutes(src->minutes_);
        timeleft_->setSeconds(src->seconds_);
    }

    NextStatus getNextStatus() const {
        if (is_break_)
            return NextStatus::Working;
        if (short_break_times_ < clock_options_->shortBreaksBeforeLong()) {
            return NextStatus::ShortBreak;
        }
        return NextStatus::LongBreak;
    }
};

}  // namespace lon

#endif  // TIMESTATUS_H
