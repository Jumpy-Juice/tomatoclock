#include "Translate.h"

// 添加这行，包含 QLabel 的完整定义头文件
#include <QLabel>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QFocusEvent>
#include <algorithm>
#include <cassert>
#include <QtGlobal>

#ifdef LON_WINDOWS
#include <windows.h>
#endif

static int translate_box_height = 70;

enum HOT_KEY_ID {
    ACTIVE_WINDOW
};

#define  APP_KEY "4e7ef943af307886"
#define  APP_SECRET "V742c09iOArGyM4eNyloBCqls7Ba1NKL"

Translate::Translate(QWidget* parent)
    : QWidget(parent) {
    // 设置无边框窗口（关键：移除系统边框才能显示圆角）
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 设置半透明背景（关键：让背景透明，只显示圆角区域）
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 设置样式表（圆角+边框+背景色）- 柔和蓝色风格
    this->setStyleSheet(
        "QWidget {"
        "background-color: #e6f2ff;"  // 淡蓝色背景
        "border-radius: 15px;"        // 增大圆角
        "border: 2px solid #4a89dc;"  // 蓝色边框
        "}"
        );

    vertical_layout_p_ = new QVBoxLayout(this);
    line_edit_p_ = new QLineEdit(this);

    QFont font;
    font.setFamily(QString::fromUtf8("宋体"));  // 修改为宋体
    font.setPointSize(18);
    line_edit_p_->setFont(font);
    line_edit_p_->setDragEnabled(true);

    vertical_layout_p_->setContentsMargins(0, 0, 0, 0);
    line_edit_p_->setFixedHeight(translate_box_height);
    line_edit_p_->installEventFilter(this);

    vertical_layout_p_->addWidget(line_edit_p_);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                         Qt::WindowMinimizeButtonHint |
                         Qt::WindowStaysOnTopHint);
    this->setMinimumWidth(650);
    this->setFixedHeight(translate_box_height);
    this->setFocusPolicy(Qt::StrongFocus);
    // 修改信号槽连接语法
    connect(this,
            &Translate::translateResult,
            this,
            &Translate::displayResult);
    resgisterHotKey();
}

void Translate::youdaoTranslate(const QString& source) {
    QString baseUrl = QString("http://openapi.youdao.com/api");

    int salt = 2;

    QByteArray data_array;
    data_array.append("q=");
    data_array.append(source.toUtf8().toPercentEncoding());
    data_array.append("&from=");
    data_array.append("auto");
    data_array.append("&to=");
    data_array.append("auto");
    data_array.append("&appKey=");
    data_array.append(APP_KEY);
    data_array.append("&salt=");
    data_array.append(QString::number(salt).toUtf8());
    data_array.append("&sign=");
    data_array.append(getYoudaoSign(source, salt));

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply_p = manager->post(request, data_array);
    connect(reply_p,
            &QNetworkReply::finished,
            this,
            [=]()
            {
                if (reply_p->error() != QNetworkReply::NoError) {
                    qDebug() << "Error String : " << reply_p->errorString();
                } else {
                    QByteArray reply_data = reply_p->readAll();

                    qDebug() << reply_data;

                    QJsonParseError error;
                    QJsonDocument json_document = QJsonDocument::fromJson(reply_data, &error);
                    if (error.error == QJsonParseError::NoError) {
                        if (!(json_document.isNull() || json_document.isEmpty()) && json_document.isObject()) {
                            QVariantMap data = json_document.toVariant().toMap();
                            const int error_code = data[QLatin1String("errorCode")].toInt();

                            if (0 == error_code) {
                                std::vector<QString> result;
                                QVariantList detailList = data[QLatin1String("translation")].toList();
                                QString str = detailList.first().toString();
                                result.push_back(str);

                                auto basicMap = data[QLatin1String("basic")].toMap();
                                auto detailTranslations = basicMap[QLatin1String("explains")].toList();
                                for (int i = 0; i < detailTranslations.size(); ++i) {
                                    result.push_back(detailTranslations.at(i).toString());
                                }

                                emit translateResult(result);
                            }
                        }
                    } else {
                        qDebug() << "Error String : " << error.errorString();
                    }
                }

                reply_p->deleteLater();
            });
}

QByteArray Translate::getYoudaoSign(const QString& source, int salt) {
    QByteArray sign;

    QString str = APP_KEY + source + QString::number(salt) + APP_SECRET;

    sign = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5).toHex().toUpper();
    return sign;
}

void Translate::resgisterHotKey() {
#ifdef LON_WINDOWS
    RegisterHotKey((HWND)winId(), ACTIVE_WINDOW, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 'M');
#endif
}

void Translate::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Cancel:
        hideWindow();
        break;
    case Qt::Key_Enter:
        doTranSlate();
        break;
    default:
        break;
    }
}

void Translate::focusOutEvent(QFocusEvent* event) {
    Q_UNUSED(event);

    hideWindow();
}

bool Translate::eventFilter(QObject* watched, QEvent* event) {
    Q_UNUSED(watched);

    if (event->type() == QEvent::KeyPress) {
        auto key_event = dynamic_cast<QKeyEvent*>(event);
        switch (key_event->key()) {
        case Qt::Key_Escape:
        case Qt::Key_Cancel:
            hideWindow();
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            doTranSlate();
            break;
        default:
            break;
        }
    } else if (event->type() == QEvent::FocusOut) {
        hideWindow();
    }
    return false;
}

bool Translate::nativeEvent(const QByteArray& eventType, void* message, qintptr* result) {
    Q_UNUSED(result);

    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY) {
            switch (msg->wParam) {
            case ACTIVE_WINDOW:
                activeWindowListener();
                break;
            default:
                assert(0 && "unhandled message from windows");
            }
        }
    }
    return false;
}

void Translate::hideWindow() {
    this->window()->setVisible(false);
    clearResultDisplaying();
}

void Translate::activeWindowListener() {
    if (this->isVisible())
        hideWindow();
    else {
        this->show();
        this->activateWindow();
        line_edit_p_->setFocus();
    }
}

void Translate::doTranSlate() {
    clearResultDisplaying();
    auto source = line_edit_p_->text();
    if (!source.isEmpty())
        youdaoTranslate(source);
}

void Translate::clearResultDisplaying() {
    while (vertical_layout_p_->count() > 1) {
        delete vertical_layout_p_->takeAt(1)->widget();
    }
    this->setFixedHeight(translate_box_height);
}

void Translate::displayResult(std::vector<QString> result) {
    QFont font;
    font.setFamily(QString::fromUtf8("宋体"));  // 保持原字体
    font.setPointSize(16);

    result.erase(std::unique(result.begin(), result.end()), result.end());

    // 先清理原有结果
    clearResultDisplaying();

    for (const auto& i : result) {
        // 使用 QLabel 来显示翻译结果，支持自动换行
        auto label = new QLabel(this);
        label->setWordWrap(true);  // QLabel 开启文本换行
        label->setText(i);
        label->setFont(font);
        label->setStyleSheet(
            "QLabel {"
            "background-color: #e6f2ff;"  // 保持背景色和主窗口一致
            "border-radius: 0px;"         // 取消子控件圆角
            "border: none;"               // 取消子控件边框
            "padding-left: 10px;"
            "color: #336699;"  // 深蓝色文字
            "}"
            );
        label->setMinimumHeight(30);    // 设置最小高度避免过矮
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        vertical_layout_p_->addWidget(label);

        // 强制更新以计算实际高度
        label->adjustSize();
        int textHeight = label->sizeHint().height();
        label->setFixedHeight(qMax(translate_box_height / 2, textHeight));  // 保持合理高度
    }

    // 调整窗口总高度
    int totalHeight = translate_box_height;  // 输入框高度
    for (int i = 1; i < vertical_layout_p_->count(); ++i) {  // 从第1个结果控件开始（索引1）
        QWidget* widget = vertical_layout_p_->itemAt(i)->widget();
        if (widget) {
            totalHeight += widget->height();
        }
    }
    this->setFixedHeight(totalHeight);
}
