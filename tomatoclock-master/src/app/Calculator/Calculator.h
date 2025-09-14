#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>
#include <QRegularExpression>  // 关键：显式包含正则表达式头文件

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_b1_clicked();

    void on_b2_clicked();

    void on_b3_clicked();

    void on_b4_clicked();

    void on_b5_clicked();

    void on_b6_clicked();

    void on_b7_clicked();

    void on_b8_clicked();

    void on_b9_clicked();

    void on_b0_clicked();

    void on_ab_clicked();

    void on_sb_clicked();

    void on_mb_clicked();

    void on_db_clicked();

    void on_cb_clicked();

    void on_deb_clicked();


    void on_eb_clicked();

    void on_lb_clicked();

    void on_rb_clicked();

private:
    Ui::Calculator *ui;
    QString expression;
};
#endif // CALCULATOR_H
