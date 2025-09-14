/********************************************************************************
** Form generated from reading UI file 'Calculator.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculator
{
public:
    QPushButton *cb;
    QPushButton *sb;
    QPushButton *deb;
    QPushButton *b8;
    QPushButton *b9;
    QPushButton *mb;
    QPushButton *b1;
    QPushButton *eb;
    QPushButton *rb;
    QPushButton *b7;
    QPushButton *ab;
    QPushButton *b4;
    QPushButton *b5;
    QPushButton *b6;
    QPushButton *db;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *lb;
    QPushButton *b0;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName("Calculator");
        Calculator->resize(357, 532);
        cb = new QPushButton(Calculator);
        cb->setObjectName("cb");
        cb->setGeometry(QRect(20, 110, 80, 80));
        cb->setMinimumSize(QSize(80, 80));
        cb->setMaximumSize(QSize(31, 16777215));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        font.setItalic(false);
        cb->setFont(font);
        sb = new QPushButton(Calculator);
        sb->setObjectName("sb");
        sb->setGeometry(QRect(180, 110, 80, 80));
        sb->setMinimumSize(QSize(80, 80));
        sb->setMaximumSize(QSize(31, 16777215));
        sb->setFont(font);
        deb = new QPushButton(Calculator);
        deb->setObjectName("deb");
        deb->setGeometry(QRect(260, 110, 80, 80));
        deb->setMinimumSize(QSize(80, 80));
        deb->setMaximumSize(QSize(31, 16777215));
        deb->setFont(font);
        b8 = new QPushButton(Calculator);
        b8->setObjectName("b8");
        b8->setGeometry(QRect(100, 190, 80, 80));
        b8->setMinimumSize(QSize(80, 80));
        b8->setMaximumSize(QSize(31, 16777215));
        b8->setFont(font);
        b9 = new QPushButton(Calculator);
        b9->setObjectName("b9");
        b9->setGeometry(QRect(180, 190, 80, 80));
        b9->setMinimumSize(QSize(80, 80));
        b9->setMaximumSize(QSize(31, 16777215));
        b9->setFont(font);
        mb = new QPushButton(Calculator);
        mb->setObjectName("mb");
        mb->setGeometry(QRect(260, 190, 80, 80));
        mb->setMinimumSize(QSize(80, 80));
        mb->setMaximumSize(QSize(31, 16777215));
        mb->setFont(font);
        b1 = new QPushButton(Calculator);
        b1->setObjectName("b1");
        b1->setGeometry(QRect(20, 350, 80, 80));
        b1->setMinimumSize(QSize(80, 80));
        b1->setMaximumSize(QSize(31, 16777215));
        b1->setFont(font);
        eb = new QPushButton(Calculator);
        eb->setObjectName("eb");
        eb->setGeometry(QRect(260, 350, 80, 161));
        eb->setMinimumSize(QSize(80, 80));
        eb->setMaximumSize(QSize(31, 16777215));
        eb->setFont(font);
        rb = new QPushButton(Calculator);
        rb->setObjectName("rb");
        rb->setGeometry(QRect(180, 430, 80, 80));
        rb->setMinimumSize(QSize(80, 80));
        rb->setMaximumSize(QSize(31, 16777215));
        rb->setFont(font);
        b7 = new QPushButton(Calculator);
        b7->setObjectName("b7");
        b7->setGeometry(QRect(20, 190, 80, 80));
        b7->setMinimumSize(QSize(80, 80));
        b7->setMaximumSize(QSize(31, 16777215));
        b7->setFont(font);
        ab = new QPushButton(Calculator);
        ab->setObjectName("ab");
        ab->setGeometry(QRect(100, 110, 80, 80));
        ab->setMinimumSize(QSize(80, 80));
        ab->setMaximumSize(QSize(31, 16777215));
        ab->setFont(font);
        b4 = new QPushButton(Calculator);
        b4->setObjectName("b4");
        b4->setGeometry(QRect(20, 270, 80, 80));
        b4->setMinimumSize(QSize(80, 80));
        b4->setMaximumSize(QSize(31, 16777215));
        b4->setFont(font);
        b5 = new QPushButton(Calculator);
        b5->setObjectName("b5");
        b5->setGeometry(QRect(100, 270, 80, 80));
        b5->setMinimumSize(QSize(80, 80));
        b5->setMaximumSize(QSize(31, 16777215));
        b5->setFont(font);
        b6 = new QPushButton(Calculator);
        b6->setObjectName("b6");
        b6->setGeometry(QRect(180, 270, 80, 80));
        b6->setMinimumSize(QSize(80, 80));
        b6->setMaximumSize(QSize(31, 16777215));
        b6->setFont(font);
        db = new QPushButton(Calculator);
        db->setObjectName("db");
        db->setGeometry(QRect(260, 270, 80, 80));
        db->setMinimumSize(QSize(80, 80));
        db->setMaximumSize(QSize(31, 16777215));
        db->setFont(font);
        b2 = new QPushButton(Calculator);
        b2->setObjectName("b2");
        b2->setGeometry(QRect(100, 350, 80, 80));
        b2->setMinimumSize(QSize(80, 80));
        b2->setMaximumSize(QSize(31, 16777215));
        b2->setFont(font);
        b3 = new QPushButton(Calculator);
        b3->setObjectName("b3");
        b3->setGeometry(QRect(180, 350, 80, 80));
        b3->setMinimumSize(QSize(80, 80));
        b3->setMaximumSize(QSize(31, 16777215));
        b3->setFont(font);
        lb = new QPushButton(Calculator);
        lb->setObjectName("lb");
        lb->setGeometry(QRect(20, 430, 80, 80));
        lb->setMinimumSize(QSize(80, 80));
        lb->setMaximumSize(QSize(31, 16777215));
        lb->setFont(font);
        b0 = new QPushButton(Calculator);
        b0->setObjectName("b0");
        b0->setGeometry(QRect(100, 430, 80, 80));
        b0->setMinimumSize(QSize(80, 80));
        b0->setMaximumSize(QSize(31, 16777215));
        b0->setFont(font);
        lineEdit = new QLineEdit(Calculator);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 20, 321, 80));
        lineEdit->setMinimumSize(QSize(20, 80));
        lineEdit->setMaximumSize(QSize(1000000, 16777215));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setItalic(false);
        lineEdit->setFont(font1);
        lineEdit->setMaxLength(1000000);

        retranslateUi(Calculator);

        QMetaObject::connectSlotsByName(Calculator);
    } // setupUi

    void retranslateUi(QWidget *Calculator)
    {
        Calculator->setWindowTitle(QCoreApplication::translate("Calculator", "Widget", nullptr));
        cb->setText(QCoreApplication::translate("Calculator", "C", nullptr));
        sb->setText(QCoreApplication::translate("Calculator", "-", nullptr));
        deb->setText(QCoreApplication::translate("Calculator", "\342\206\220", nullptr));
        b8->setText(QCoreApplication::translate("Calculator", "8", nullptr));
        b9->setText(QCoreApplication::translate("Calculator", "9", nullptr));
        mb->setText(QCoreApplication::translate("Calculator", "*", nullptr));
        b1->setText(QCoreApplication::translate("Calculator", "1", nullptr));
        eb->setText(QCoreApplication::translate("Calculator", "=", nullptr));
        rb->setText(QCoreApplication::translate("Calculator", "\357\274\211", nullptr));
        b7->setText(QCoreApplication::translate("Calculator", "7", nullptr));
        ab->setText(QCoreApplication::translate("Calculator", "+", nullptr));
        b4->setText(QCoreApplication::translate("Calculator", "4", nullptr));
        b5->setText(QCoreApplication::translate("Calculator", "5", nullptr));
        b6->setText(QCoreApplication::translate("Calculator", "6", nullptr));
        db->setText(QCoreApplication::translate("Calculator", "/", nullptr));
        b2->setText(QCoreApplication::translate("Calculator", "2", nullptr));
        b3->setText(QCoreApplication::translate("Calculator", "3", nullptr));
        lb->setText(QCoreApplication::translate("Calculator", "\357\274\210", nullptr));
        b0->setText(QCoreApplication::translate("Calculator", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
