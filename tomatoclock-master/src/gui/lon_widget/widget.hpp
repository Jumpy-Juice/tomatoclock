#ifndef LON_WIDGET
#define LON_WIDGET

#include "button.hpp"
#include "titlebar.hpp"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QScreen>
#include <QGuiApplication>
#include <cassert>

namespace lon {
class Widget : public QWidget {
    Q_OBJECT
private:
    TitleBar* title_bar_;

    QSizeGrip* size_grip_;

    Button* ok_button_;
    Button* cancel_button_;

    QGridLayout* p_layout_;

    bool size_girp_enabled;

    QPixmap* pixmap_;

    qint64 last_time_epoch_{0};
    qint64 reset_background_time_{40};

    QTimer timer_;
    bool   block_one_;

protected:
    QWidget* center_widget_;
    QWidget* bottom_bar_;

private:
    virtual void setLayout(QLayout*) {}

    void initLayout() {
        p_layout_ = new QGridLayout(this);
        p_layout_->setSpacing(0);
        p_layout_->addWidget(title_bar_, 0, 0, 1, 2);
        p_layout_->addWidget(center_widget_, 1, 0, 1, 2);
        p_layout_->addWidget(bottom_bar_, 2, 0, 1, 1);
        p_layout_->setContentsMargins(0, 0, 0, 0);
    }

    void initBottomBar() {
        bottom_bar_->setFixedHeight(50);
        bottom_bar_->setWindowFlags(Qt::SubWindow);

        QHBoxLayout* bottom_layout = new QHBoxLayout(bottom_bar_);

        ok_button_ = new Button(bottom_bar_);
        cancel_button_ = new Button(bottom_bar_);

        ok_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:hover{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:pressed{border-image: url(:/icon/Resources/button.png);} ");
        ok_button_->setText(u8"确认");
        ok_button_->setFixedSize(90, 30);
        ok_button_->setFlat(true);

        cancel_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:hover{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:pressed{border-image: url(:/icon/Resources/button.png);} ");

        cancel_button_->setText(u8"取消");
        cancel_button_->setFixedSize(90, 30);
        cancel_button_->setFlat(true);

        bottom_layout->addStretch();
        bottom_layout->addWidget(ok_button_);
        bottom_layout->addStretch();
        bottom_layout->addWidget(cancel_button_);
        bottom_layout->addStretch();

        bottom_bar_->setLayout(bottom_layout);
    }

    void initConnect() {
        connect(ok_button_, &QPushButton::clicked, this, &Widget::onOkButtonClicked);
        connect(cancel_button_, &QPushButton::clicked, this, &Widget::onCancelButtonClicked);
        connect(title_bar_, &TitleBar::minimizeButtonClicked, this, &Widget::minimizeButtonClicked);
        connect(title_bar_, &TitleBar::maximizeButtonClicked, this, &Widget::maximizeButtonClicked);
        connect(title_bar_, &TitleBar::closeButtonClicked, this, &Widget::closeButtonClicked);
        connect(&timer_, &QTimer::timeout, [this]() {
            this->setBackground(pixmap_);
            block_one_ = false;
        });
    }

    void initWidgets() {
        pixmap_ = nullptr;
        timer_.setSingleShot(true);
        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
        title_bar_->setPalette(palette);
    }

protected:
    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);
        sizeChanged(event);
        if (pixmap_ == nullptr)
            return;
        if (pixmap_->isNull())
            return;
        const auto current_epoch = QDateTime::currentMSecsSinceEpoch();
        if (last_time_epoch_ == 0) {
            this->setBackground(pixmap_);
        } else if (current_epoch - last_time_epoch_ >= reset_background_time_) {
            this->setBackground(pixmap_);
        } else {
            if (!block_one_) {
                timer_.start(reset_background_time_);
                block_one_ = true;
            } else {
                timer_.stop();
                this->setBackground(pixmap_);
                block_one_ = false;
            }
        }
        last_time_epoch_ = current_epoch;
    }

public:
    explicit Widget(QWidget* parent = nullptr, TitleBar::Buttons status = TitleBar::ALL)
        : QWidget(parent) {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        title_bar_ = new TitleBar(this, status);
        center_widget_ = new QWidget();
        bottom_bar_ = new QWidget();
        size_girp_enabled = false;

        initWidgets();
        initBottomBar();
        initLayout();
        initConnect();
    }

    explicit Widget(QWidget* center_widget, QWidget* bottom_bar, QWidget* parent = nullptr)
        : QWidget(parent) {
        assert(center_widget && "pointer cannot be null");
        assert(bottom_bar && "pointer cannot be null");
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

        title_bar_ = new TitleBar(this);

        center_widget_ = center_widget;
        bottom_bar_ = bottom_bar;

        initWidgets();
        initLayout();
        initConnect();
    }

    virtual ~Widget() {
        delete pixmap_;
        delete center_widget_;
        delete bottom_bar_;
    }

    qint64 getResetBackgroundTime() const {
        return reset_background_time_;
    }

    void setResetBackgroundTime(const qint64 reset_background_time) {
        reset_background_time_ = reset_background_time;
    }

    QWidget* centerWidget() const {
        return center_widget_;
    }

    virtual bool setBottomBar(QWidget* widget) {
        p_layout_->removeWidget(bottom_bar_);

        delete bottom_bar_;

        bottom_bar_ = widget;
        if (bottom_bar_)
            p_layout_->addWidget(bottom_bar_, 2, 0, 1, 1);
        return true;
    }

    virtual bool setCenterWidget(QWidget* widget) {
        if (!widget)
            return false;

        p_layout_->removeWidget(center_widget_);

        delete center_widget_;
        center_widget_ = widget;

        if (center_widget_)
            p_layout_->addWidget(center_widget_, 1, 0);
        return true;
    }

    QWidget* bottomBar() const {
        return bottom_bar_;
    }
    virtual void setTitle(const QString& title) {
        title_bar_->setTitle(title);
    }

    virtual void setTitleIcon(const QIcon& icon) {
        title_bar_->setTitleIcon(icon);
    }

    virtual void setTitleBackground(QPixmap* pixmap) {
        title_bar_->setBackground(pixmap);
    }

    virtual void enabelSizeGrip() {
        size_girp_enabled = true;
        size_grip_ = new QSizeGrip(this);
        size_grip_->setFixedSize(size_grip_->sizeHint());
        p_layout_->addWidget(size_grip_, 2, 1, Qt::AlignRight | Qt::AlignBottom);
    }

    virtual bool sizeGripEnabled() {
        return size_girp_enabled;
    }

    virtual void setBackground(QPixmap* pixmap) {
        this->setAutoFillBackground(true);
        if (pixmap->isNull()) {
            qDebug() << tr("illege arguments, your image is empty") << __FILE__ << "\n";
            return;
        }
        QPalette palette = this->palette();
        auto     brush =
            QBrush(pixmap->scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        palette.setBrush(this->backgroundRole(), std::move(brush));
        this->setPalette(palette);
        pixmap_ = pixmap;
    }

    virtual void setMinFunc(std::function<void(void)> val) {
        title_bar_->setMinFunc(val);
    }

    virtual void setMaxFunc(std::function<void(void)> val) {
        title_bar_->setMaxFunc(val);
    }

    virtual void setCloseFunc(std::function<void(void)> val) {
        title_bar_->setCloseFunc(val);
    }

    // 窗口居中显示
    void moveToCenter() {
        // 获取屏幕几何信息
        QScreen* screen = QGuiApplication::primaryScreen();
        if (screen) {
            QRect screenGeometry = screen->geometry();
            QRect windowGeometry = this->geometry();
            
            // 计算居中位置
            int x = (screenGeometry.width() - windowGeometry.width()) / 2;
            int y = (screenGeometry.height() - windowGeometry.height()) / 2;
            
            // 移动窗口到居中位置
            this->move(x, y);
        }
    }

signals:
    void okButtonClicked();
    void cancelButtonClicked();
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();
    void sizeChanged(QResizeEvent* event);
private slots:
    void onOkButtonClicked() {
        emit okButtonClicked();
    }

    void onCancelButtonClicked() {
        emit cancelButtonClicked();
    }
};

class ShadowWindow : public QWidget {
    Q_OBJECT
public:
    explicit ShadowWindow(QWidget* contentWidget, QWidget* parent = nullptr)
        : QWidget(parent) {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(contentWidget);
        shadowEffect->setColor(Qt::lightGray);
        shadowEffect->setBlurRadius(6);
        shadowEffect->setOffset(0, 0);
        contentWidget->setGraphicsEffect(shadowEffect);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(contentWidget);
        layout->setContentsMargins(4, 4, 4, 4);
        setLayout(layout);

        contentWidget->installEventFilter(this);
    }
    bool eventFilter(QObject* watched, QEvent* event) override {
        if (watched->isWidgetType() && event->type() == QEvent::Resize) {
            QWidget* widget = static_cast<QWidget*>(watched);
            this->resize(widget->size().width() + 8, widget->size().height() + 8);
        }
        return QWidget::eventFilter(watched, event);
    }


public slots:
    void sizeChanged(QResizeEvent* event) {
        this->resize(event->size().width() + 8, event->size().height() + 8);
    }
};
}  // namespace lon

#endif

