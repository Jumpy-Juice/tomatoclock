#include "clockmainwidget.h"
#include "chartswidget.h"
#include "clockrunningwidget.h"
#include "labelsandtargetswidget.h"
#include "menu.hpp"
#include "messagebox.hpp"
#include "settingfileoperations.h"
#include "settingwidget.h"
#include "../../tc/tc/clocksql.hpp"
#include "Translate.h"
#include "Calculator.h"
#include "tomatoclocktimer.h"

#include <QGridLayout>
#include <QSystemTrayIcon>
#include <QApplication>
// PRIVATE
void lon::ClockMainWidget::tomatoSaveToSql() {
    auto time_status = &timer->timerStatus();

    // 计算总的工作时间（秒）
    int total_work_seconds = time_status->options()->workTime()->minutes_ * 60 + 
                            time_status->options()->workTime()->seconds_;
    
    // 计算剩余时间（秒）
    int remaining_seconds = time_status->timeleft()->minutes() * 60 + 
                           time_status->timeleft()->seconds();
    
    // 计算已过去的时间（秒）
    int passed_seconds = total_work_seconds - remaining_seconds;
    
    // 转换为分钟（向上取整，确保不丢失时间）
    int passed_minutes = (passed_seconds + 59) / 60;  // 等同于 ceil(passed_seconds / 60.0)
    
    // 如果工作时间超过3分钟则记录（防止误触记录）
    if (passed_minutes >= 3) {
        qDebug() << "记录番茄钟: " << passed_minutes << "分钟, 标签:" << running_clock_label_name_ << ", 目标:" << running_clock_target_name_;
        
        bool success = sql_p_->addAFinishedTomato(
            static_cast<uint8_t>(passed_minutes), 
            running_clock_label_name_, 
            running_clock_target_name_);
            
        if (success) {
            // 记录成功后更新统计数据
            updateStatisticsData();
        } else {
            qDebug() << "警告：番茄钟记录保存失败！";
        }
    } else {
        qDebug() << "番茄钟时间过短(" << passed_minutes << "分钟)，未记录";
    }
}

void lon::ClockMainWidget::updateStatisticsData() {
    // 重新从数据库获取最新的统计数据
    *today_data_p_ = sql_p_->getTodayData();
    *lastweek_data_p_ = sql_p_->getLastWeekData();
    *lastmonth_data_p_ = sql_p_->getLastMonthData();
    
    qDebug() << "统计数据已更新";
    
    // 如果当前显示的是主界面，需要通知界面更新目标widget中的统计显示
    // 这个操作比较重，所以我们通过重绘整个界面来确保数据同步
    if (labels_targets_widget_p_) {
        // 发射重绘信号，让主界面刷新
        emit labels_targets_widget_p_->redrawWidget();
    }
}

void lon::ClockMainWidget::saveSettingToFile(const ClockOptions& options) {
    SettingFileOperations::saveClockOptionToFile(options);
    
    // 如果计时器正在运行，则更新其设置
    if (timer) {
        timer->updateSettings();
    }
    
    if (setting_widget_p_) {
        setting_widget_p_->deleteLater();
        setting_widget_p_ = nullptr;
    }
}

void lon::ClockMainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            showMainWindow();
            break;
        default:
            break;
    }
}

void lon::ClockMainWidget::showMainWindow() {
    if (!this->isVisible() || this->window()->isMinimized()) {
        // 窗口隐藏或最小化时，显示并激活窗口
        this->window()->show();
        this->window()->showNormal();      // 确保不是最小化状态
        this->window()->raise();           // 将窗口提升到最前面
        this->window()->activateWindow();  // 激活窗口
    } else if (this->window()->isActiveWindow()) {
        // 如果窗口已经是活动窗口，则隐藏到托盘
        this->window()->hide();
        system_tray_icon_p_->showMessage(
            QString(u8"番茄钟"),
            QString(u8"程序已最小化到系统托盘"),
            QSystemTrayIcon::Information,
            2000
        );
    } else {
        // 窗口可见但不是活动窗口（被其他窗口遮挡），提升到前面
        this->window()->raise();
        this->window()->activateWindow();
    }
}

void lon::ClockMainWidget::showTranslateWindow() {
    if (!translate_widget_p_) {
        // 延迟创建翻译窗口，避免程序启动时就注册热键
        translate_widget_p_ = new Translate();
        translate_widget_p_->hide();  // 确保创建时是隐藏的
    }
    
    if (translate_widget_p_->isVisible()) {
        // 如果翻译窗口已经显示，则隐藏它
        translate_widget_p_->hide();
    } else {
        // 显示翻译窗口
        translate_widget_p_->show();
        translate_widget_p_->raise();
        translate_widget_p_->activateWindow();
    }
}

void lon::ClockMainWidget::showCalculatorWindow() {
    if (!calculator_widget_p_) {
        // 延迟创建计算器窗口
        calculator_widget_p_ = new Calculator();
        calculator_widget_p_->hide();  // 确保创建时是隐藏的
    }
    
    if (calculator_widget_p_->isVisible()) {
        // 如果计算器窗口已经显示，则隐藏它
        calculator_widget_p_->hide();
    } else {
        // 显示计算器窗口
        calculator_widget_p_->show();
        calculator_widget_p_->raise();
        calculator_widget_p_->activateWindow();
    }
}

lon::ClockMainWidget::ClockMainWidget(QWidget* parent)
    : Widget(parent),
      keep_working_(false),
      sql_p_(ClockSql::instance()),
      today_data_p_(new tomato_clock::TodayData(sql_p_->getTodayData())),
      lastweek_data_p_(new tomato_clock::LastWeekData(sql_p_->getLastWeekData())),
      lastmonth_data_p_(new tomato_clock::LastMonthData(sql_p_->getLastMonthData())) {
    // this->setWindowFlags(Qt::FramelessWindowHint |
    // Qt::WindowMinimizeButtonHint);
    // title_bar_p_ = new lon::TitleBar(this);

    QIcon window_icon(":/icon/Icons/tomato.png");

    system_tray_icon_p_ = new QSystemTrayIcon(this);
    system_tray_icon_p_->setIcon(window_icon);
    system_tray_icon_p_->setToolTip(QString(u8"TMT"));
    system_tray_icon_p_->show();

    close_action_p_ = new QAction(QString(u8"退出番茄钟"), this);
    about_action_p_ = new QAction(QString(u8"关于"), this);
    setting_action_p_ = new QAction(QString(u8"设置"), this);
    show_action_p_ = new QAction(QString(u8"显示主窗口"), this);
    translate_action_p_ = new QAction(QString(u8"翻译"), this);
    calculator_action_p_ = new QAction(QString(u8"计算器"), this);

    menu_p_ = new Menu(this);

    // addAction will take ownship of pointers.
    menu_p_->addAction(show_action_p_);
    menu_p_->addSeparator();
    menu_p_->addAction(translate_action_p_);
    menu_p_->addAction(calculator_action_p_);
    menu_p_->addAction(about_action_p_);
    menu_p_->addAction(setting_action_p_);
    menu_p_->addSeparator();
    menu_p_->addAction(close_action_p_);

    system_tray_icon_p_->setContextMenu(menu_p_);

    labels_targets_widget_p_ =
        new LabelsAndTargetsWidget(lastweek_data_p_, lastmonth_data_p_, this);
    clock_running_widget_p_ = nullptr;
    chart_widget_p_ = nullptr;

    timer = nullptr;

    main_layout_ = new QVBoxLayout();
    main_layout_->addWidget(labels_targets_widget_p_);
    // Qt6 推荐使用新的信号槽连接语法
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::startClock,
            this,
            &ClockMainWidget::displayClock);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::changeSetting,
            this,
            &ClockMainWidget::displaySetting);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::showChart,
            this,
            &ClockMainWidget::displayChart);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::showCalculator,
            this,
            &ClockMainWidget::showCalculatorWindow);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::showTranslate,
            this,
            &ClockMainWidget::showTranslateWindow);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::redrawWidget,
            this,
            &ClockMainWidget::displayTarget);
    this->centerWidget()->setLayout(main_layout_);
    QWidget* temp = new QWidget(this);
    temp->setMaximumHeight(50);
    this->setBottomBar(temp);

    this->enabelSizeGrip();
    // 设置标题栏的背景图.
    this->setTitleBackground(new QPixmap(":/all/Res/Img/titlebarbackground.png"));
    // 设置程序背景
    this->setBackground(new QPixmap(":/all/Res/Img/background.png"));
    // this->resize(1050, 700);
    this->setMinimumSize(950, 650);
    // 设置大小策略，允许窗口在全屏时正确调整
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 设置窗口大小调整策略，确保最大化时不会变小
    this->setWindowState(Qt::WindowNoState);

    this->setWindowIcon(window_icon);
    this->setTitleIcon(window_icon);
    this->setTitle(QString(u8"番茄钟"));

    connect(close_action_p_, &QAction::triggered, this, &ClockMainWidget::exitApplication);
    connect(setting_action_p_, &QAction::triggered, this, &ClockMainWidget::displaySetting);
    connect(show_action_p_, &QAction::triggered, this, &ClockMainWidget::showMainWindow);
    connect(translate_action_p_, &QAction::triggered, this, &ClockMainWidget::showTranslateWindow);
    connect(calculator_action_p_, &QAction::triggered, this, &ClockMainWidget::showCalculatorWindow);

    connect(
        system_tray_icon_p_, &QSystemTrayIcon::activated, this, &ClockMainWidget::iconActivated);

    // 修改关闭按钮行为：直接退出程序而不是隐藏到托盘
    Widget::setCloseFunc([this]() { 
        exitApplication();
    });
    
    // 设置最小化按钮行为：隐藏到系统托盘而不是最小化到任务栏
    this->setMinFunc([this]() {
        this->window()->hide();
        system_tray_icon_p_->showMessage(
            QString(u8"番茄钟"),
            QString(u8"程序已最小化到系统托盘，双击托盘图标或右键选择'显示主窗口'来恢复"),
            QSystemTrayIcon::Information,
            3000
        );
    });
}

lon::ClockMainWidget::~ClockMainWidget() {
    qDebug() << "ClockMainWidget析构函数被调用";
    
    // 确保定时器被停止
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    
    // 删除所有组件
    delete sql_p_;
    delete labels_targets_widget_p_;
    delete clock_running_widget_p_;
    delete chart_widget_p_;
    delete translate_widget_p_;
    delete calculator_widget_p_;
    
    qDebug() << "ClockMainWidget析构完成";
}

void lon::ClockMainWidget::displayClock(const QString& label, const QString& target) {
    if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }

    if (!timer) {
        timer = new TomatoClockTimer(this);
        connect(timer, &TomatoClockTimer::tomatoFinished, this, &ClockMainWidget::clockFinished);
    } else {
        // 确保使用最新的设置
        timer->updateSettings();
    }
    timer->start();

    running_clock_label_name_ = label;
    running_clock_target_name_ = target;

    clock_running_widget_p_ =
        new ClockRunningWidget(running_clock_label_name_, running_clock_target_name_);
    clock_running_widget_p_->setTimer(timer);
    main_layout_->addWidget(clock_running_widget_p_);

    // Qt6 推荐使用新的信号槽连接语法
    connect(clock_running_widget_p_,
            &ClockRunningWidget::clockStoped,
            this,
            &ClockMainWidget::clockBreaked);
}

void lon::ClockMainWidget::displayTarget() {
    // 切换界面时, 操作不会很频繁, 故不保留原界面.
    if (clock_running_widget_p_) {
        main_layout_->removeWidget(clock_running_widget_p_);
        delete clock_running_widget_p_;
        clock_running_widget_p_ = nullptr;
    } else if (chart_widget_p_) {
        main_layout_->removeWidget(chart_widget_p_);
        delete chart_widget_p_;
        chart_widget_p_ = nullptr;
    } else if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }

    labels_targets_widget_p_ = new LabelsAndTargetsWidget(lastweek_data_p_, lastmonth_data_p_);
    main_layout_->addWidget(labels_targets_widget_p_);

    // connections
    // Qt6 推荐使用新的信号槽连接语法
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::startClock,
            this,
            &ClockMainWidget::displayClock);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::changeSetting,
            this,
            &ClockMainWidget::displaySetting);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::showChart,
            this,
            &ClockMainWidget::displayChart);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::showCalculator,
            this,
            &ClockMainWidget::showCalculatorWindow);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::showTranslate,
            this,
            &ClockMainWidget::showTranslateWindow);
    connect(labels_targets_widget_p_,
            &LabelsAndTargetsWidget::redrawWidget,
            this,
            &ClockMainWidget::displayTarget);
}

void lon::ClockMainWidget::displayChart() {
    if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }
    chart_widget_p_ = new ChartsWidget(today_data_p_, lastweek_data_p_, lastmonth_data_p_);
    // # background
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
    chart_widget_p_->setPalette(palette);
    main_layout_->addWidget(chart_widget_p_);
    connect(
        chart_widget_p_, &ChartsWidget::closeButtonClicked, this, &ClockMainWidget::displayTarget);
}

void lon::ClockMainWidget::clockFinished() {
    // 在提前结束番茄钟时, 只有已经超过三分钟的才可以被记录.
    tomatoSaveToSql();
    if (timer->timerStatus().options()->keepWorking()) {
        timer->start();
    } else {
        new lon::MessageBoxWrapper(QString(u8"番茄完成"), QString(u8"番茄已完成."));
        displayTarget();
    }
}

    void lon::ClockMainWidget::clockBreaked() {
    tomatoSaveToSql();
    timer->stop();
    timer->clear();
    new lon::MessageBoxWrapper(QString(u8"番茄中断"), QString(u8"已中断, 完成数据已储存."));
    displayTarget();
}

    // 这个要写在函数体外
    void lon::ClockMainWidget::displaySetting() {
        if (!setting_widget_p_) {
            setting_widget_p_ = new SettingWidget();
            connect(setting_widget_p_,
                    &SettingWidget::settingChanged,
                    this,
                    &ClockMainWidget::saveSettingToFile);
        }
        setting_widget_p_->show();
    }

void lon::ClockMainWidget::exitApplication() {
    qDebug() << "开始退出应用程序...";
    
    // 如果番茄钟正在运行，先保存数据并停止定时器
    if (timer) {
        if (clock_running_widget_p_) {
            tomatoSaveToSql();
        }
        // 停止番茄钟定时器
        timer->stop();
        qDebug() << "番茄钟定时器已停止";
    }
    
    // 关闭所有子窗口
    if (translate_widget_p_) {
        translate_widget_p_->close();
        translate_widget_p_->deleteLater();
        qDebug() << "翻译窗口已关闭";
    }
    if (calculator_widget_p_) {
        calculator_widget_p_->close();
        calculator_widget_p_->deleteLater();
        qDebug() << "计算器窗口已关闭";
    }
    if (setting_widget_p_) {
        setting_widget_p_->close();
        setting_widget_p_->deleteLater();
        qDebug() << "设置窗口已关闭";
    }
    
    // 隐藏系统托盘图标
    if (system_tray_icon_p_) {
        system_tray_icon_p_->hide();
        qDebug() << "系统托盘图标已隐藏";
    }
    
    // 确保所有事件都被处理
    QApplication::processEvents();
    
    qDebug() << "强制退出应用程序";
    // 强制退出应用程序
    QApplication::quit();
}

