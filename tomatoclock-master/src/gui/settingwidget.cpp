#include "../../tc/tc/settingwidget.h"

SettingWidget::SettingWidget(QWidget* parent) : lon::Widget(parent) {
    widget_p_ = new SettingWidgetPrivate(this);
    this->setCenterWidget(widget_p_);
    this->setBottomBar(nullptr);
    this->setFixedSize(800, 550);
    this->setCloseFunc([this]() { this->close(); });
    connect(this, &lon::Widget::closeButtonClicked, this, &SettingWidget::closingWindow);
}

void SettingWidget::closingWindow() {
    emit settingChanged(*widget_p_->clockOptionSetted());
}