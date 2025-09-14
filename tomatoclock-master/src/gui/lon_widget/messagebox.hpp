#ifndef LON_MESSAGEBOX
#define LON_MESSAGEBOX
#include "widget.hpp"
#include <QMessageBox>
#include <QLabel>
#include <QBoxLayout>
#include <QHBoxLayout>


namespace lon {
class MessageBox : public Widget {
    Q_OBJECT
private:
    QLabel*     text_label_p_;
    QBoxLayout* center_layout_p_;
public:
    MessageBox(QWidget* parent = nullptr) : Widget(parent) {}
    MessageBox(const QString& title, const QString& message, QWidget* parent = nullptr)
        : Widget(parent) {
        setTitle(title);
        text_label_p_ = new QLabel(this);
        text_label_p_->setText(message);
        center_layout_p_ = new QHBoxLayout(this);
        center_layout_p_->addStretch();
        center_layout_p_->addWidget(text_label_p_);
        center_layout_p_->addStretch();
        centerWidget()->setLayout(center_layout_p_);

        connect(this, &MessageBox::okButtonClicked,
                this, &MessageBox::onOkButtonClicked);
        connect(this, &MessageBox::cancelButtonClicked,
                this, &MessageBox::onCancleButtonClicked);

        this->setWindowFlag(Qt::Dialog);
        this->setCloseFunc([this]() { this->close(); });
        this->setAttribute(Qt::WA_DeleteOnClose);
        
        // 窗口居中显示
        this->show();
        this->moveToCenter();
    }
private slots:
    void onOkButtonClicked() {
        window()->close();
    }
    void onCancleButtonClicked() {
        window()->close();
    }
};

class MessageBoxWrapper : public QObject {
    Q_OBJECT
private:
    // 不允许初始化在栈上.
    ~MessageBoxWrapper() = default;
protected:
    lon::MessageBox* message_box_p_;
    virtual void closeAndDelete() {
        if (message_box_p_) {
            message_box_p_->window()->close();
            delete message_box_p_;
            message_box_p_ = nullptr;
        }
        this->deleteLater(); // 删除wrapper对象自身
    }
public:
    MessageBoxWrapper(const QString& title, const QString& message, QObject* parent = nullptr)
        : QObject(parent), message_box_p_(nullptr) {
        message_box_p_ = new lon::MessageBox(title, message);

        connect(message_box_p_, &MessageBox::closeButtonClicked,
                this, &MessageBoxWrapper::onCloseButtonClicked);
        connect(message_box_p_, &MessageBox::okButtonClicked,
                this, &MessageBoxWrapper::onOkButtonClicked);
        connect(message_box_p_, &MessageBox::cancelButtonClicked,
                this, &MessageBoxWrapper::onCancelButtonClicked);
    }

public slots:
    virtual void onCloseButtonClicked() {
        closeAndDelete();
    }
    virtual void onOkButtonClicked() {
        closeAndDelete();
    }
    virtual void onCancelButtonClicked() {
        closeAndDelete();
    }
};

}  // namespace lon
#endif
