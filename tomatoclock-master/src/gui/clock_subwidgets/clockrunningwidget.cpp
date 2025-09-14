#include "../../tc/tc/clockrunningwidget.h"
#include "../../tc/tc/button.hpp"
#include "tomatoclocktimer.h"
#include <QLabel>

void lon::ClockRunningWidget::setReceiveTimerWidget(DisplayClockBase* displaye_p) {
    current_display_widget_p_ = displaye_p;
    if (timer_p_)
        timer_p_->setDisplayClock(current_display_widget_p_);
}


void lon::ClockRunningWidget::setTimer(TomatoClockTimer* timer) {
    timer_p_ = timer;
    timer_p_->setDisplayClock(current_display_widget_p_);
}

lon::ClockRunningWidget::ClockRunningWidget(const QString label_name,
                                            const QString target_name,
                                            QWidget* parent)
    : QWidget(parent) {
    timer_p_ = nullptr;

    main_display_widget_p_ = new ClockDisplayWidget(this);
    main_layout_p_ = new QGridLayout(this);
    main_layout_p_->addWidget(main_display_widget_p_, 0, 0, 1, 2);
    label_label_p_ = new QLabel(this);
    label_label_p_->setText(label_name);
    label_label_p_->setMaximumSize(QSize(16777215, 50));
    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font.setPointSize(20);
    font.setBold(true);
    label_label_p_->setFont(font);
    label_label_p_->setAlignment(Qt::AlignCenter);
    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor{qRgba(255,235,59,150)});
    label_label_p_->setPalette(palette);
    main_layout_p_->addWidget(label_label_p_, 1, 0, 1, 2);
    target_label_p_ = new QLabel(this);
    palette.setColor(QPalette::WindowText, QColor{qRgba(255,235,59,150)});
    target_label_p_->setPalette(palette);
    target_label_p_->setText(target_name);
    target_label_p_->setMaximumSize(QSize(16777215, 50));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font1.setPointSize(20);
    font1.setBold(true);
    target_label_p_->setFont(font1);
    target_label_p_->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    main_layout_p_->addWidget(target_label_p_, 2, 0, 1, 2);
    stop_button_p_ = new Button(this);
    stop_button_p_->setMaximumSize(QSize(40, 40));
    main_layout_p_->addWidget(stop_button_p_, 3, 0, 1, 1);
    small_window_switch_button_p_ = new Button(this);
    small_window_switch_button_p_->setMaximumSize(QSize(40, 40));
    main_layout_p_->addWidget(small_window_switch_button_p_, 3, 1, 1, 1);

    setReceiveTimerWidget(main_display_widget_p_);

    stop_button_p_->setFlat(true);
    stop_button_p_->setFixedSize(45, 45);
    stop_button_p_->setStyleSheet("border:none");
    stop_button_p_->setNormal(new QIcon(":/icon/Icons/stop_normal.png"));
    stop_button_p_->setFocus(new QIcon(":/icon/Icons/stop_focus.png"));
    stop_button_p_->setPressed(new QIcon(":/icon/Icons/stop_pressed.png"));
    stop_button_p_->setToolTip(u8"停止番茄钟");

    small_window_switch_button_p_->setFlat(true);
    small_window_switch_button_p_->setFixedSize(45, 45);
    small_window_switch_button_p_->setStyleSheet("border:none");
    small_window_switch_button_p_->setNormal(new QIcon(":/icon/Icons/small_window_normal.png"));
    small_window_switch_button_p_->setFocus(new QIcon(":/icon/Icons/small_window_focus.png"));
    small_window_switch_button_p_->setPressed(new QIcon(":/icon/Icons/small_window_pressed.png"));
    small_window_switch_button_p_->setToolTip(u8"小窗口显示");

    connect(stop_button_p_, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
    connect(
        small_window_switch_button_p_, SIGNAL(clicked()), this, SLOT(onSmallWindowButtonClicked()));

}

void lon::ClockRunningWidget::onStopButtonClicked() {
    emit clockStoped();
}

void lon::ClockRunningWidget::onSmallWindowButtonClicked() {
    this->window()->setVisible(false);
    small_window_p_ =
        new clock_window::ClockSmallWindow(label_label_p_->text(), target_label_p_->text());
    this->setReceiveTimerWidget(small_window_p_->progress_widget_);
    small_window_p_->show();
    connect(small_window_p_, SIGNAL(clockStoped()), this, SIGNAL(clockStoped()));
    connect(small_window_p_, SIGNAL(smallWindowClosing()), this, SLOT(backToCurrentWidget()));
    connect(small_window_p_, SIGNAL(requestShowMainWindow()), this, SLOT(backToCurrentWidget()));
}

void lon::ClockRunningWidget::backToCurrentWidget() {
    this->setReceiveTimerWidget(main_display_widget_p_);
    small_window_p_->window()->close();
    small_window_p_->deleteLater();  // 使用延迟删除避免闪退
    small_window_p_ = nullptr;
    this->window()->setVisible(true);
}
