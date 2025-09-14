/********************************************************************************
** Form generated from reading UI file 'text.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_text
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *text)
    {
        if (text->objectName().isEmpty())
            text->setObjectName("text");
        text->resize(800, 600);
        centralwidget = new QWidget(text);
        centralwidget->setObjectName("centralwidget");
        text->setCentralWidget(centralwidget);
        menubar = new QMenuBar(text);
        menubar->setObjectName("menubar");
        text->setMenuBar(menubar);
        statusbar = new QStatusBar(text);
        statusbar->setObjectName("statusbar");
        text->setStatusBar(statusbar);

        retranslateUi(text);

        QMetaObject::connectSlotsByName(text);
    } // setupUi

    void retranslateUi(QMainWindow *text)
    {
        text->setWindowTitle(QCoreApplication::translate("text", "text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class text: public Ui_text {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXT_H
