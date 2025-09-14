#include "../../tc/tc/addlabelwidget.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif

lon::AddLabelWidget::AddLabelWidget(const std::list<QString> labels, QWidget* parent)
    : Widget(parent, TitleBar::CLOSE_MIN), labels_(labels) {
    line_edit_p_ = new QLineEdit(this);
    label_p_ = new QLabel(this);
    center_layout_p_ = new QHBoxLayout(this);

    label_p_->setText(QString{"标签名: "});
    label_p_->setFocus();
    line_edit_p_->setPlaceholderText(QString{"请输入标签名, 标签名不可重复."});
    center_layout_p_->addWidget(label_p_);
    center_layout_p_->addWidget(line_edit_p_);
    centerWidget()->setLayout(center_layout_p_);

    this->setStyleSheet(
        "QWidget {"
        "background-color: rgb(255, 250, 205);"
        "}"
    );
    // 设置"标签名"文本为黄色，字体变大
    label_p_->setStyleSheet(
        "QLabel {"
        "color: rgb(255, 215, 0);"
        "font-weight: bold;"
        "font-size: 16px;"
        "}"
    );
    
    // 设置输入框样式：背景白色，字体变大
    line_edit_p_->setStyleSheet(
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
    this->setCloseFunc([this]() { this->setVisible(false); });

    this->resize(QSize(400,250));
    connect(this, &AddLabelWidget::okButtonClicked, this, &AddLabelWidget::onOkButtonClicked);
}

void lon::AddLabelWidget::setLabels(const std::list<QString> labels) {
    labels_ = labels;
}

void lon::AddLabelWidget::labelExists() {
    showMessage(QString{"标签已存在, 请重新输入."});
}

void lon::AddLabelWidget::onOkButtonClicked() {
    QString input(line_edit_p_->text());
    auto    iter = std::find(labels_.begin(), labels_.end(), input);
    if (iter != labels_.end())
        labelExists();
    else {
        emit labelAdded(input);
    }
}

void lon::AddLabelWidget::closeMessagebox() {
    if (messagebox_p_) {
        messagebox_p_->window()->close();
        delete messagebox_p_;
        messagebox_p_ = nullptr;
    }
    setLineEditFocus();
}

void lon::AddLabelWidget::setLineEditFocus() {
    line_edit_p_->setFocus(Qt::OtherFocusReason);
    line_edit_p_->selectAll();
}

void lon::AddLabelWidget::showMessage(const QString& message) {
    // bug memeory leak here
    messagebox_p_ = new lon::MessageBox("", message);
    connect(
        messagebox_p_, &lon::MessageBox::okButtonClicked, this, &AddLabelWidget::closeMessagebox);
    connect(messagebox_p_,
            &lon::MessageBox::cancelButtonClicked,
            this,
            &AddLabelWidget::closeMessagebox);
    connect(messagebox_p_,
            &lon::MessageBox::closeButtonClicked,
            this,
            &AddLabelWidget::setLineEditFocus);
}
