#include "../../tc/tc/clockdisplaywidget.h"

lon::ClockDisplayWidget::ClockDisplayWidget(QWidget* parent)
    : DisplayClockBase(parent),
    left_time_string_p_(std::make_unique<QString>()) {
    working_foreground_brush_ = std::make_unique<QBrush>(QColor(255, 87, 34));       // 橘色
    shortbreaking_foreground_brush_ = std::make_unique<QBrush>(QColor(3, 169, 244)); // 蓝色
    longbreaking_foreground_brush_ = std::make_unique<QBrush>(QColor(76, 175, 80));  // 绿色

    current_brush_ = working_foreground_brush_.get();  // 默认初始为工作状态
}

void lon::ClockDisplayWidget::updateTimeDisplay(const TimerStatus* timer_status) {
    timer_status_ = timer_status;
    ClockTime const* total_time = timer_status->currentStageTotalTime();

    current_persent_ = currentPersent(timer_status);
    left_time_string_p_ = leftTimeString(timer_status);

    if (total_time_ != total_time) {
        if (total_time == timer_status->options()->workTime()) {
            current_brush_ = working_foreground_brush_.get();
        } else if (total_time == timer_status->options()->shortBreakTime()) {
            current_brush_ = shortbreaking_foreground_brush_.get();
        } else {
            current_brush_ = longbreaking_foreground_brush_.get();
        }
        total_time_ = total_time;
    }

    update();
}


void lon::ClockDisplayWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    double m_rotateAngle = current_persent_ * 360.0;

    // 调整绘制区域，确保圆圈不会被裁剪
    int penWidth = 20;  // 圆圈粗细
    int margin = penWidth + 10;  // 边距 = 圆圈粗细 + 额外边距
    int side = qMin(width(), height()) - 2 * margin;
    QRectF outRect(margin, margin, side, side);
    p.setPen(QPen(current_brush_->color(), penWidth));

    p.drawArc(outRect, (90 - m_rotateAngle) * 16, m_rotateAngle * 16);

    //画文字
    if (left_time_string_p_ == nullptr)
        return;
    QFont f = QFont("Microsoft YaHei", 40, QFont::Bold);
    p.setFont(f);
    p.drawText(outRect, Qt::AlignCenter, *left_time_string_p_);
}


