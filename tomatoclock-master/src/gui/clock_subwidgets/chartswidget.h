#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include "clocksql.hpp"
#include <QWidget>
#include <memory>

class QComboBox;
class QLabel;
class QGridLayout;
class QVBoxLayout;

namespace lon {
class ListWidget;
class Button;
}  // namespace lon

#include <QtCharts/QChart>
#include <QtCharts/QChartView>

namespace lon {
/*!
 * \class ChartsWidget
 *
 * \brief 显示图表类, 包括两个折线图, 两个饼图.
 *
 * \author LON
 */
class ChartsWidget : public QWidget {
    Q_OBJECT
private:
    QComboBox* finish_line_combobox_p_;
    QComboBox* finishedtime_line_combobox_p_;
    QComboBox* label_pie_combobox_p_;
    QComboBox* target_pie_combobox_p_;

    QLabel* finish_line_label_p_;
    QLabel* finishedtime_line_label_p_;
    QLabel* label_pie_label_p_;
    QLabel* target_pie_label_p_;

    QWidget* finish_line_widget_p_;
    QWidget* finishedtime_line_widget_p_;
    QWidget* label_pie_widget_p_;
    QWidget* target_pie_widget_p_;

    QGridLayout* finish_line_layout_p_;
    QGridLayout* finishedtime_line_layout_p_;
    QGridLayout* label_pie_layout_p_;
    QGridLayout* target_pie_layout_p_;

    ClockSql* sql_;

    std::shared_ptr<tomato_clock::TodayData>     todaydata_p_;
    std::shared_ptr<tomato_clock::LastWeekData>  lastweekdata_p_;
    std::shared_ptr<tomato_clock::LastMonthData> lastmonthdata_p_;
    std::shared_ptr<tomato_clock::LastYearData>  lastyeardata_p_;

    // todo 在listwidget的右边显示一个指示栏。
    ListWidget* list_widget_p_;
    Button*     close_button_p_;

    QVBoxLayout* layout_p_;

    // 现在可以直接使用 QChartView 和 QChart，不需要 QtCharts:: 前缀
    QChartView* day_finish_line_chart_view_p_;
    QChartView* week_finish_line_chart_view_p_;
    QChartView* month_finish_line_chart_view_p_;
    QChartView* week_finishedtime_line_chart_view_p_;
    QChartView* month_finishedtime_line_chart_view_p_;
    QChartView* day_finishedtime_line_chart_view_p_;
    QChartView* day_labels_pie_chart_view_p_;
    QChartView* week_labels_pie_chart_view_p_;
    QChartView* month_labels_pie_chart_view_p_;
    QChartView* day_targets_pie_chart_view_p_;
    QChartView* week_targets_pie_chart_view_p_;
    QChartView* month_targets_pie_chart_view_p_;
    QChartView* bestworktime_chart_view_p_;

    QChart* finished_day_line_chart_p_;
    QChart* finished_week_line_chart_p_;
    QChart* finished_month_line_chart_p_;

    QChart* finishedtime_week_line_chart_p_;
    QChart* finishedtime_month_line_chart_p_;
    QChart* finishedtime_day_line_chart_p_;

    QChart* day_labels_piechart_chart_p_;
    QChart* week_labels_piechart_chart_p_;
    QChart* month_labels_piechart_chart_p_;

    QChart* day_targets_piechart_chart_p_;
    QChart* week_targets_piechart_chart_p_;
    QChart* month_targets_piechart_chart_p_;

    /// <summary>
    /// 以data_array初始化一个包含QLineSeries的Chart.
    /// </summary>
    /// <param name="data_array">生成的series所用的数据.</param>
    /// <param name="title">生成series的标题.</param>
    /// <returns>生成的chart的指针.</returns>
    template <size_t Size>
    QChart* initLineChartSeries(const std::array<uint16_t, Size>& data_array,
                                QString                           title = QString());
    /// <summary>
    /// 以labels_data初始化一个包含QPieSeries的Chart.
    /// </summary>
    /// <param name="labels_data">生成series所用的数据.</param>
    /// <param name="title">series的标题.</param>
    /// <returns>生成的chart的指针.</returns>
    QChart* initPieChartSeries(std::vector<std::pair<QString, int>> labels_data,
                               QString                              title = QString());

    // init charts
    void initDayFinishedLineChart();
    void initWeekFinishedLineChart();
    void initMonthFinishedLineChart();
    void initWeekFinishedTimeLineChart();
    void initMonthFinishedTimeLineChart();
    void initDayFinishedTimeLineChart();
    void initFinishedTimeLineChart();
    void initDayLabelsPieChart();
    void initWeekLabelsPieChart();
    void initMonthLabelsPieChart();
    void initDayTargetsPieChart();
    void initWeekTargetsPieChart();
    void initMonthTargetsPieChart();
    void initBestworkTimeChart();

    // init widgets.
    void initFinishLinewidget();
    void initFinishedTimeLinewidget();
    void initLabelsPieWidget();
    void initTargetsPieWidget();
    void initBestworkTimeWidget();

public:
    explicit ChartsWidget(std::shared_ptr<tomato_clock::TodayData>     todaydata_p,
                          std::shared_ptr<tomato_clock::LastWeekData>  lastweekdata_p,
                          std::shared_ptr<tomato_clock::LastMonthData> lastmonthdata_p,
                          QWidget*                                     parent = nullptr);
    ~ChartsWidget();

signals:
    void closeButtonClicked();
public slots:
    // 每个图的时间段切换事件.
    void finishLineWidgetSwitchEvent(int index);
    void finishedTimeLineWidgetSwitchEvent(int index);
    void labelsPieWidgetSwitchEvent(int index);
    void targetsPieWidgetSwitchEvent(int index);
};
}  // namespace lon

#endif  // CHARTSWIDGET_H
