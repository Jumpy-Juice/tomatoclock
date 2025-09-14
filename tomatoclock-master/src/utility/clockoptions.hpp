#ifndef CLOCKOPTIONS_H
#define CLOCKOPTIONS_H

#include <QTime>
#include <cstdint>
#include <memory>

namespace lon {

// 所有时间结构基类
struct ClockTime {
    int8_t minutes_;
    int8_t seconds_;

    ClockTime(int8_t minutes, int8_t seconds) : minutes_(minutes), seconds_(seconds) {}
};

class ClockOptions {
private:
    std::unique_ptr<ClockTime> work_time_;
    std::unique_ptr<ClockTime> short_break_time_;
    std::unique_ptr<ClockTime> long_break_time_;
    int8_t                     short_breaks_before_long_ = 3;
    bool                       keep_working_ = false;

public:
    ClockOptions()
        : work_time_(std::make_unique<ClockTime>(25, 0)),
          short_break_time_(std::make_unique<ClockTime>(5, 0)),
          long_break_time_(std::make_unique<ClockTime>(15, 0)) {}

    ClockOptions(int8_t work_min,
                 int8_t work_sec,
                 int8_t sb_min,
                 int8_t sb_sec,
                 int8_t lb_min,
                 int8_t lb_sec,
                 int8_t sb_count,
                 bool   keep)
        : work_time_(std::make_unique<ClockTime>(work_min, work_sec)),
          short_break_time_(std::make_unique<ClockTime>(sb_min, sb_sec)),
          long_break_time_(std::make_unique<ClockTime>(lb_min, lb_sec)),
          short_breaks_before_long_(sb_count),
          keep_working_(keep) {}

    ClockOptions(const ClockOptions& other)
        : work_time_(std::make_unique<ClockTime>(*other.work_time_)),
          short_break_time_(std::make_unique<ClockTime>(*other.short_break_time_)),
          long_break_time_(std::make_unique<ClockTime>(*other.long_break_time_)),
          short_breaks_before_long_(other.short_breaks_before_long_),
          keep_working_(other.keep_working_) {}

    ClockOptions& operator=(const ClockOptions& other) {
        if (this != &other) {
            work_time_ = std::make_unique<ClockTime>(*other.work_time_);
            short_break_time_ = std::make_unique<ClockTime>(*other.short_break_time_);
            long_break_time_ = std::make_unique<ClockTime>(*other.long_break_time_);
            short_breaks_before_long_ = other.short_breaks_before_long_;
            keep_working_ = other.keep_working_;
        }
        return *this;
    }

    ClockOptions(ClockOptions&&) noexcept = default;
    ClockOptions& operator=(ClockOptions&&) noexcept = default;

    ~ClockOptions() = default;

    bool setWorkTime(int8_t min, int8_t sec) {
        if (min < 0 || sec < 0 || sec >= 60 || min > 100)
            return false;
        work_time_->minutes_ = min;
        work_time_->seconds_ = sec;
        return true;
    }

    bool setShortBreakTime(int8_t min, int8_t sec) {
        if (min < 0 || sec < 0 || sec >= 60 || min > 100)
            return false;
        short_break_time_->minutes_ = min;
        short_break_time_->seconds_ = sec;
        return true;
    }

    bool setLongBreakTime(int8_t min, int8_t sec) {
        if (min < 0 || sec < 0 || sec >= 60 || min > 100)
            return false;
        long_break_time_->minutes_ = min;
        long_break_time_->seconds_ = sec;
        return true;
    }

    const ClockTime* workTime() const {
        return work_time_.get();
    }

    const ClockTime* shortBreakTime() const {
        return short_break_time_.get();
    }

    const ClockTime* longBreakTime() const {
        return long_break_time_.get();
    }

    int8_t shortBreaksBeforeLong() const {
        return short_breaks_before_long_;
    }

    void setShortBreaksBeforeLong(int8_t count) {
        short_breaks_before_long_ = count;
    }

    bool keepWorking() const {
        return keep_working_;
    }

    void setKeepWorking(bool value) {
        keep_working_ = value;
    }
};

}  // namespace lon

#endif  // CLOCKOPTIONS_H
