#pragma once

#ifdef _WIN32
#define LON_WINDOWS
#else
#endif // _WIN32

#ifdef LON_WINDOWS
#include <windows.h>
// 取消Windows API中与Qt冲突的宏定义
#ifdef MessageBox
#undef MessageBox
#endif
#endif

#include <QWidget>
#include <QtGlobal>

// 前向声明用到的类
class QLineEdit;
class QVBoxLayout;
class QLabel;

class Translate : public QWidget {
    Q_OBJECT

public:
    Translate(QWidget* parent = nullptr);

    void youdaoTranslate(const QString& source);
    QByteArray getYoudaoSign(const QString& source, int salt);

    void resgisterHotKey();
protected:
    void keyPressEvent(QKeyEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;

    bool eventFilter(QObject* watched, QEvent* event) override;

    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
private:
    QVBoxLayout* vertical_layout_p_;
    QLineEdit* line_edit_p_;

    void hideWindow();
    void activeWindowListener();
    void doTranSlate();
    void clearResultDisplaying();

public slots:
    void displayResult(std::vector<QString>);
signals:
    void translateResult(std::vector<QString>);
};
