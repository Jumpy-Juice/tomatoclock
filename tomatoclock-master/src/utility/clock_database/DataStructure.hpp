#pragma once

#include <QString>
#include <array>
#include <cstdint>
#include <utility>
#include <vector>

namespace lon::tomato_clock {

template <size_t len_num>
struct ChartDataBase {
    std::array<uint16_t, len_num>        time_data_p{};
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    ChartDataBase() = default;
    ChartDataBase(const ChartDataBase&) = default;
    ChartDataBase(ChartDataBase&&) noexcept = default;
    ChartDataBase& operator=(const ChartDataBase&) = default;
    ChartDataBase& operator=(ChartDataBase&&) noexcept = default;
    ~ChartDataBase() = default;
};

template <size_t len_num>
struct ChartDataWithTotalTime : public ChartDataBase<len_num> {
    using Base = ChartDataBase<len_num>;
    std::array<uint16_t, len_num> total_time_p{};

    ChartDataWithTotalTime() = default;
    ChartDataWithTotalTime(const ChartDataWithTotalTime&) = default;
    ChartDataWithTotalTime(ChartDataWithTotalTime&&) noexcept = default;
    ChartDataWithTotalTime& operator=(const ChartDataWithTotalTime&) = default;
    ChartDataWithTotalTime& operator=(ChartDataWithTotalTime&&) noexcept = default;
    ~ChartDataWithTotalTime() = default;
};

// 数据类型别名
using TodayData = ChartDataWithTotalTime<24>;
using LastWeekData = ChartDataWithTotalTime<7>;
using LastMonthData = ChartDataWithTotalTime<31>;
using LastYearData = ChartDataWithTotalTime<366>;

}  // namespace lon::tomato_clock
