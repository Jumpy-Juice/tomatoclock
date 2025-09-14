#ifndef LON_TITLEBAR
#define LON_TITLEBAR

#include "button.hpp"
#include <QApplication>
#include <QEvent>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <cassert>
#include <functional>
#include <memory>

namespace lon {
class TitleBar : public QWidget {
    Q_OBJECT
private:
    static const int32_t BUTTON_HEIGHT = 45;
    static const int32_t BUTTON_WIDTH = 45;
    static const int32_t TITLE_BAR_HEIGHT = 50;

    QLabel* icon_label_;
    QLabel* title_label_;

    Button* pminimize_button_;
    Button* pmaximize_button_;
    Button* pclose_button_;

    std::shared_ptr<QIcon> max_max_normal_;
    std::shared_ptr<QIcon> max_max_focus_;
    std::shared_ptr<QIcon> max_max_pressed_;

    std::shared_ptr<QIcon> max_normal_normal_;
    std::shared_ptr<QIcon> max_normal_focus_;
    std::shared_ptr<QIcon> max_normal_pressed_;

    QPixmap* pixmap_;

    QHBoxLayout* title_bar_layout_;

    bool   is_pressed_;
    QPoint move_start_position_;

    std::function<void(void)> min_func_;
    std::function<void(void)> max_func_;
    std::function<void(void)> close_func_;

private:
    void updateMaximize() {
        QWidget* pWindow = this->window();
        if (pWindow->isWindow()) {
            bool bMaximize = pWindow->isMaximized();
            if (bMaximize) {
                pmaximize_button_->setToolTip(tr("还原"));
                pmaximize_button_->setProperty("maximizeProperty", "restore");

                pmaximize_button_->setNormal(max_max_normal_);
                pmaximize_button_->setFocus(max_max_focus_);
                pmaximize_button_->setPressed(max_max_pressed_);
            } else {
                pmaximize_button_->setProperty("maximizeProperty", "maximize");
                pmaximize_button_->setToolTip(tr("最大化"));

                pmaximize_button_->setNormal(max_normal_normal_);
                pmaximize_button_->setFocus(max_normal_focus_);
                pmaximize_button_->setPressed(max_normal_pressed_);
            }
            pmaximize_button_->setStyle(QApplication::style());
        }
    }

    void initWidgets(int32_t button) {
        const char minn = 4;
        const char maxn = 2;

        if ((button & minn) == minn) {
            pminimize_button_ = new Button(new QIcon(":/icon/Resources/min_normal.png"),
                                           new QIcon(":/icon/Resources/min_focus.png"),
                                           new QIcon(":/icon/Resources/min_pressed.png"),
                                           this);
            pminimize_button_->setFlat(true);
            pminimize_button_->setStyleSheet("border:none");
            pminimize_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
            pminimize_button_->setObjectName("minimizeButton");
            pminimize_button_->setToolTip("最小化");
        }

        if ((button & maxn) == maxn) {
            pmaximize_button_ = new Button(this);

            pmaximize_button_->setNormal(max_normal_normal_);
            pmaximize_button_->setFocus(max_normal_focus_);
            pmaximize_button_->setPressed(max_normal_pressed_);
            pmaximize_button_->setFlat(true);
            pmaximize_button_->setStyleSheet("border:none");
            pmaximize_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
            pmaximize_button_->setObjectName("maximizeButton");
            pmaximize_button_->setToolTip("最大化");
        }

        pclose_button_ = new Button(new QIcon(":/icon/Resources/close_normal.png"),
                                    new QIcon(":/icon/Resources/close_focus.png"),
                                    new QIcon(":/icon/Resources/close_pressed.png"),
                                    this);
        pclose_button_->setFlat(true);
        pclose_button_->setStyleSheet("border:none");
        pclose_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
        pclose_button_->setObjectName("closeButton");
        pclose_button_->setToolTip("关闭窗口");

        icon_label_ = new QLabel(this);
        icon_label_->setFixedSize(30, 30);
        icon_label_->setScaledContents(true);

        title_label_ = new QLabel(this);
        title_label_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        title_label_->setObjectName("titleLable");
    }

    void initLayout(int32_t button) {
        const char minn = 4;
        const char maxn = 2;
        title_bar_layout_ = new QHBoxLayout(this);
        title_bar_layout_->addWidget(icon_label_);
        title_bar_layout_->addSpacing(5);
        title_bar_layout_->addWidget(title_label_);
        title_bar_layout_->setSpacing(0);

        if ((button & minn) == minn)
            title_bar_layout_->addWidget(pminimize_button_);
        if ((button & maxn) == maxn)
            title_bar_layout_->addWidget(pmaximize_button_);
        title_bar_layout_->addWidget(pclose_button_);

        title_bar_layout_->setContentsMargins(5, 0, 0, 0);

        this->setLayout(title_bar_layout_);
    }

    void initConnection(int32_t button) {
        const char minn = 4;
        const char maxn = 2;

        if ((button & minn) == minn)
            connect(pminimize_button_, &QPushButton::clicked, this, &TitleBar::onButtonClicked);
        if ((button & maxn) == maxn)
            connect(pmaximize_button_, &QPushButton::clicked, this, &TitleBar::onButtonClicked);
        connect(pclose_button_, &QPushButton::clicked, this, &TitleBar::onButtonClicked);
    }

    void initMaxIcons(int32_t button) {
        const char maxn = 2;
        if ((button & maxn) != maxn)
            return;

        max_max_normal_.reset(new QIcon(":/icon/Resources/max_max_normal.png"));
        max_max_focus_.reset(new QIcon(":/icon/Resources/max_max_focus.png"));
        max_max_pressed_.reset(new QIcon(":/icon/Resources/max_max_pressed.png"));

        max_normal_normal_.reset(new QIcon(":/icon/Resources/max_normal_normal.png"));
        max_normal_focus_.reset(new QIcon(":/icon/Resources/max_normal_focus.png"));
        max_normal_pressed_.reset(new QIcon(":/icon/Resources/max_normal_pressed.png"));
    }

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override {
        Q_UNUSED(event);
        emit pmaximize_button_->clicked();
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (this->window()->isMaximized())
            return;

        is_pressed_ = true;
        move_start_position_ = event->globalPosition().toPoint();
        QWidget::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (!is_pressed_)
            return;

        QPoint move_point = event->globalPosition().toPoint() - move_start_position_;
        QPoint widget_pos = this->window()->pos();

        move_start_position_ = event->globalPosition().toPoint();
        this->window()->move(widget_pos.x() + move_point.x(), widget_pos.y() + move_point.y());
        QWidget::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        is_pressed_ = false;
        QWidget::mouseReleaseEvent(event);
    }

    bool eventFilter(QObject* obj, QEvent* event) override {
        switch (event->type()) {
        case QEvent::WindowTitleChange: {
            QWidget* pWidget = qobject_cast<QWidget*>(obj);
            if (pWidget) {
                title_label_->setText(pWidget->windowTitle());
                return true;
            }
            return false;
        }
        case QEvent::WindowIconChange: {
            QWidget* pWidget = qobject_cast<QWidget*>(obj);
            if (pWidget) {
                QIcon icon = pWidget->windowIcon();
                icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
                return true;
            }
            return false;
        }
        case QEvent::WindowStateChange:
        case QEvent::Resize:
            this->updateMaximize();
            return true;
        default:
            return QWidget::eventFilter(obj, event);
        }
    }

public:
    enum Buttons { CLOSE = 1, CLOSE_MAX = 3, CLOSE_MIN = 5, ALL = 7 };

    explicit TitleBar(QWidget* parent, Buttons button = ALL) : QWidget(parent) {
        assert(parent && "the parent of titlebar cannot be empty");

        is_pressed_ = false;
        pixmap_ = nullptr;

        this->resize(parent->width(), TITLE_BAR_HEIGHT);
        this->setFixedHeight(TITLE_BAR_HEIGHT);
        initMaxIcons(button);
        initWidgets(button);
        initLayout(button);
        initConnection(button);

        min_func_ = [this]() {
            if (this->window()->isWindow())
                this->window()->showMinimized();
        };
        max_func_ = [this]() {
            if (this->window()->isWindow())
                this->window()->isMaximized() ? this->window()->showNormal()
                                              : this->window()->showMaximized();
            this->updateMaximize();
        };
        close_func_ = [this]() {
            if (this->window()->isWindow())
                this->window()->close();
        };
    }

    virtual void setTitle(const QString& title) {
        title_label_->setText(title);
    }

    virtual void setTitleIcon(const QIcon& icon) {
        icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
    }

    virtual void setBackground(QPixmap* pixmap) {
        this->setAutoFillBackground(true);
        if (pixmap->isNull()) {
            qDebug().noquote() << tr("illegal arguments");
            return;
        }
        QPalette palette = this->palette();
        palette.setBrush(
            this->backgroundRole(),
            QBrush(pixmap->scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        this->setPalette(palette);
        pixmap_ = pixmap;
    }

    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);
        if (pixmap_ == nullptr)
            return;
        if (pixmap_->isNull())
            return;
        this->setBackground(pixmap_);
    }

    virtual ~TitleBar() {
        max_max_normal_ = nullptr;
        max_max_focus_ = nullptr;
        max_max_pressed_ = nullptr;

        max_normal_normal_ = nullptr;
        max_normal_focus_ = nullptr;
        max_normal_pressed_ = nullptr;

        delete pixmap_;
    }

    void setMinFunc(std::function<void(void)> val) {
        min_func_ = val;
    }

    void setMaxFunc(std::function<void(void)> val) {
        max_func_ = val;
    }

    void setCloseFunc(std::function<void(void)> val) {
        close_func_ = val;
    }

signals:
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();

private slots:
    void onButtonClicked() {
        QPushButton* pButton = qobject_cast<QPushButton*>(sender());
        if (pButton == pminimize_button_) {
            emit minimizeButtonClicked();
            min_func_();
        } else if (pButton == pmaximize_button_) {
            emit maximizeButtonClicked();
            max_func_();
        } else if (pButton == pclose_button_) {
            emit closeButtonClicked();
            close_func_();
        }
    }
};
}  // namespace lon

#endif

