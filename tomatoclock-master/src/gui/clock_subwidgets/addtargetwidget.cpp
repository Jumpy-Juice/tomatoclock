#include "../../tc/tc/addtargetwidget.h"
#include "messagebox.hpp"
#include "../../tc/tc/clocksql.hpp"

#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>

static const int window_height = 300;
static const int window_width = 500;

#pragma execution_character_set("utf-8")

lon::AddTargetWidget::AddTargetWidget(std::list<QString>& labels, QWidget* parent)
    : Widget(parent, TitleBar::CLOSE_MIN), sql_(ClockSql::instance()) {

    labels_combobox_p_ = new QComboBox(this);
    lineedit_p_ = new QLineEdit(this);
    label_p_ = new QLabel(this);
    select_label_p_ = new QLabel(this);

    select_label_p_->setText(tr("选择标签 :"));
    label_p_->setText(tr("请输入目标名 :"));

    for (const auto& label : labels) {
        labels_combobox_p_->addItem(label);
    }

    main_layout_p_ = new QGridLayout();

    main_layout_p_->addWidget(select_label_p_, 0, 0, 1, 1);
    main_layout_p_->addWidget(labels_combobox_p_, 0, 1, 1, 2);
    main_layout_p_->addWidget(label_p_, 1, 0, 1, 1);
    main_layout_p_->addWidget(lineedit_p_, 1, 1, 1, 2);

    this->centerWidget()->setLayout(main_layout_p_);

    // 设置窗口背景为淡黄色 rgb(255, 250, 205)
    this->setStyleSheet(
        "QWidget {"
        "background-color: rgb(255, 250, 205);"
        "}"
    );
    
    // 设置"选择标签"文本为黄色，字体变大
    select_label_p_->setStyleSheet(
        "QLabel {"
        "color: rgb(255, 215, 0);"
        "font-weight: bold;"
        "font-size: 16px;"
        "}"
    );
    
    // 设置"请输入目标名"文本为黄色，字体变大
    label_p_->setStyleSheet(
        "QLabel {"
        "color: rgb(255, 215, 0);"
        "font-weight: bold;"
        "font-size: 16px;"
        "}"
    );
    
    // 设置下拉框样式：背景白色，字体变大
    labels_combobox_p_->setStyleSheet(
        "QComboBox {"
        "background-color: white;"
        "border: 2px solid #ccc;"
        "border-radius: 5px;"
        "padding: 8px;"
        "font-size: 14px;"
        "min-height: 30px;"
        "}"
        "QComboBox:focus {"
        "border: 2px solid rgb(255, 215, 0);"
        "}"
        "QComboBox::drop-down {"
        "border: none;"
        "}"
        "QComboBox::down-arrow {"
        "image: url(:/icon/Icons/dropdown_arrow.png);"
        "width: 12px;"
        "height: 12px;"
        "}"
    );
    
    // 设置输入框样式：背景白色，字体变大
    lineedit_p_->setStyleSheet(
        "QLineEdit {"
        "background-color: white;"
        "border: 2px solid #ccc;"
        "border-radius: 5px;"
        "padding: 8px;"
        "font-size: 14px;"
        "min-height: 30px;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid rgb(255, 215, 0);"
        "}"
    );

    this->setWindowFlag(Qt::Dialog);
    this->setFixedSize(window_width, window_height);
    this->setCloseFunc([this]() { this->close(); });

    connect(this, &AddTargetWidget::okButtonClicked, this, &AddTargetWidget::onOkButtonClicked);
}

void lon::AddTargetWidget::onOkButtonClicked() {
    if (!sql_) {
        showMessage("数据库未初始化，操作失败。");
        return;
    }

    QString label = labels_combobox_p_->currentText();
    QString target = lineedit_p_->text();
    if (sql_->targetExists(label, target)) {
        showMessage("该标签下已存在同名目标，请重新输入。");
    } else {
        emit targetAdded(label, target);
        // 移除 this->window()->close(); 让父对象管理窗口关闭
    }
}

void lon::AddTargetWidget::showMessage(const QString& message) {
    new MessageBoxWrapper("", message); // 建议后续加 deleteOnClose 标志
}

void lon::AddTargetWidget::setLabels(std::list<QString>& labels) {
    labels_combobox_p_->clear();
    for (const auto& label : labels) {
        labels_combobox_p_->addItem(label);
    }
}

