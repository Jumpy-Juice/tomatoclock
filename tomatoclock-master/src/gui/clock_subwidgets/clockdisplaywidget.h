#ifndef CLOCKDISPLAYWIDGET_H
#define CLOCKDISPLAYWIDGET_H

#include <QPainter>
#include <QWidget>
#include <memory>

#include "displayclockbase.h"

namespace lon {

/*!
 * \class ClockDisplayWidget
 *
 * \brief 显示计时组件, 将会根据剩余时间画一个圆形进度条
 */
class ClockDisplayWidget : public DisplayClockBase {
    Q_OBJECT
private:
    double current_persent_ = 0.0;
    const ClockTime* total_time_ = nullptr;
    std::unique_ptr<QString> left_time_string_p_;
    const TimerStatus* timer_status_ = nullptr;

    // 三种状态的颜色画刷，使用 unique_ptr 管理内存
    std::unique_ptr<QBrush> working_foreground_brush_;
    std::unique_ptr<QBrush> shortbreaking_foreground_brush_;
    std::unique_ptr<QBrush> longbreaking_foreground_brush_;

    QBrush* current_brush_ = nullptr;  // 指向当前使用的 brush，不拥有资源

public:
    explicit ClockDisplayWidget(QWidget* parent = nullptr);

    /// 根据 timer_status 更新显示数据
    void updateTimeDisplay(const TimerStatus* timer_status) override;

    /// 绘制界面
    void paintEvent(QPaintEvent*) override;

signals:

public slots:
};

}  // namespace lon

#endif  // CLOCKDISPLAYWIDGET_H
