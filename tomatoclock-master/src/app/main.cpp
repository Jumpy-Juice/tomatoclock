#include "clockmainwidget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    
    // 设置应用程序属性，确保程序能够正确退出
    a.setQuitOnLastWindowClosed(true);
    
    lon::ClockMainWidget w;
    w.show();
    
    // 连接应用程序的aboutToQuit信号，确保清理工作
    QObject::connect(&a, &QApplication::aboutToQuit, [&w]() {
        qDebug() << "应用程序即将退出，执行清理工作...";
        // 这里可以添加额外的清理代码
    });
    
    return a.exec();
}
