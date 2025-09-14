#include "Calculator.h"
#include "ui_Calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    setWindowTitle("番茄钟计算器");

    // 窗口背景：柔和的天空蓝渐变
    setStyleSheet(R"(
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #f0f9ff, stop:1 #e6f4ff);
    )");

    QFont mainFont("微软雅黑", 20);
    mainFont.setBold(true);
    ui->lineEdit->setFont(mainFont);

    // 数字按钮：柔和的薄荷绿渐变
    QString numBtnStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #e0f7fa, stop:1 #b2ebf2);
            color: #006064;
            border: none;
            border-radius: 28px;
            padding: 22px;
            font: bold 22px "微软雅黑";
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #e8f9fd, stop:1 #bfeff5);
        }
    )";
    QList<QPushButton*> numButtons = {
        ui->b1, ui->b2, ui->b3, ui->b4,
        ui->b5, ui->b6, ui->b7, ui->b8,
        ui->b9, ui->b0
    };
    for (QPushButton *btn : numButtons) {
        btn->setStyleSheet(numBtnStyle);
    }

    // 运算符按钮：柔和的珊瑚色渐变
    QString opBtnStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #ffebee, stop:1 #ffcdd2);
            color: #c62828;
            border: none;
            border-radius: 28px;
            padding: 22px;
            font: bold 22px "微软雅黑";
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #fff3f5, stop:1 #ffd6da);
        }
    )";
    QList<QPushButton*> opButtons = {
        ui->ab, ui->sb, ui->mb, ui->db
    };
    for (QPushButton *btn : opButtons) {
        btn->setStyleSheet(opBtnStyle);
    }

    // 功能按钮：柔和的薰衣草紫渐变
    QString funcBtnStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #ede7f6, stop:1 #d1c4e9);
            color: #512da8;
            border: none;
            border-radius: 28px;
            padding: 22px;
            font: bold 22px "微软雅黑";
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #f3f0f9, stop:1 #d9cdf0);
        }
    )";
    QList<QPushButton*> funcButtons = {
        ui->cb, ui->deb, ui->lb, ui->rb
    };
    for (QPushButton *btn : funcButtons) {
        btn->setStyleSheet(funcBtnStyle);
    }

    // 等号按钮：柔和的青柠绿渐变
    ui->eb->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #f1f8e9, stop:1 #dcedc8);
            color: #558b2f;
            border: none;
            border-radius: 28px;
            padding: 22px;
            font: bold 22px "微软雅黑";
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #f5faf0, stop:1 #e1f3d0);
        }
    )");

    // 输入框细化：更柔和的半透明效果
    ui->lineEdit->setStyleSheet(R"(
        QLineEdit {
            background: rgba(255,255,255, 0.95);
            border: 2px solid #b39ddb;
            border-radius: 18px;
            padding: 14px;
            font: bold 22px "微软雅黑";
        }
    )");
}

Calculator::~Calculator()
{
    delete ui;
}

// 以下槽函数和工具函数保持不变...



void Calculator::on_b1_clicked()
{
    expression +="1";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b2_clicked()
{
    expression +="2";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b3_clicked()
{
    expression +="3";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b4_clicked()
{
    expression +="4";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b5_clicked()
{
    expression +="5";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b6_clicked()
{
    expression +="6";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b7_clicked()
{
    expression +="7";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b8_clicked()
{
    expression +="8";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b9_clicked()
{
    expression +="9";
    ui->lineEdit->setText(expression);
}


void Calculator::on_b0_clicked()
{
    expression +="0";
    ui->lineEdit->setText(expression);
}


void Calculator::on_ab_clicked()
{
    expression +="+";
    ui->lineEdit->setText(expression);
}


void Calculator::on_sb_clicked()
{
    expression +="-";
    ui->lineEdit->setText(expression);
}


void Calculator::on_mb_clicked()
{
    expression +="*";
    ui->lineEdit->setText(expression);
}


void Calculator::on_db_clicked()
{
    expression +="/";
    ui->lineEdit->setText(expression);
}


void Calculator::on_cb_clicked()
{
    expression.clear();
    ui->lineEdit->clear();
}


void Calculator::on_deb_clicked()
{
    expression.chop(1);
    ui->lineEdit->setText(expression);
}


bool isOperator(const QChar &ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// 获取运算符优先级：^ > *、/ > +、-
int getPriority(const QChar &op)
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// 中缀表达式转后缀表达式（逆波兰）
QString infixToPostfix(const QString &infix)
{
    QString postfix;
    QStack<QChar> opStack;

    for (const QChar &ch : infix) {
        if (ch.isDigit() || ch == '.') { // 数字或小数点，直接加入后缀
            postfix += ch;
        } else if (isOperator(ch)) {    // 运算符
            // 栈顶运算符优先级 >= 当前运算符，弹出到后缀
            while (!opStack.isEmpty()
                   && isOperator(opStack.top())
                   && getPriority(opStack.top()) >= getPriority(ch)) {
                postfix += ' '; // 用空格分隔不同token
                postfix += opStack.pop();
            }
            postfix += ' ';     // 运算符前加空格分隔
            opStack.push(ch);   // 当前运算符入栈
        } else if (ch == '(') { // 左括号入栈
            opStack.push(ch);
        } else if (ch == ')') { // 右括号，弹出到左括号
            while (!opStack.isEmpty() && opStack.top() != '(') {
                postfix += ' ';
                postfix += opStack.pop();
            }
            opStack.pop(); // 弹出左括号（不加入后缀）
        }
    }

    // 栈中剩余运算符弹出到后缀
    while (!opStack.isEmpty()) {
        postfix += ' ';
        postfix += opStack.pop();
    }

    return postfix.trimmed(); // 去掉首尾空格
}

// 计算后缀表达式（逆波兰）
double calculatePostfix(const QString &postfix)
{
    QStack<double> numStack;
    QStringList tokens = postfix.split(' ', Qt::SkipEmptyParts);

    for (const QString &token : tokens) {
        // 替换 QRegExp 为 QRegularExpression，无需额外头文件（Qt Widgets 已包含依赖）
        if (token.contains(QRegularExpression("^[0-9.]+$"))) {
            numStack.push(token.toDouble());
        } else if (isOperator(token.at(0))) {       // 运算符
            if (numStack.size() < 2) {
                // 运算符需要至少两个操作数，否则表达式错误
                return NAN;
            }
            double b = numStack.pop(); // 注意顺序：先弹出的是右操作数
            double a = numStack.pop(); // 后弹出的是左操作数
            double result = 0;

            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*") {
                result = a * b;
            } else if (token == "/") {
                if (qFuzzyCompare(b, 0.0)) { // 除数不能为0
                    return NAN;
                }
                result = a / b;
            } else if (token == "^") {
                result = pow(a, b);
            }

            numStack.push(result);
        }
    }

    // 最终栈中只剩一个结果
    return numStack.size() == 1 ? numStack.pop() : NAN;
}
// -------------- 工具函数结束 --------------

void Calculator::on_eb_clicked()
{
    // 1. 获取用户输入的表达式
    expression = ui->lineEdit->text().trimmed();
    if (expression.isEmpty()) {
        ui->lineEdit->setText("请输入表达式");
        return;
    }

    // 2. 中缀转后缀
    QString postfix = infixToPostfix(expression);

    // 3. 计算后缀表达式
    double result = calculatePostfix(postfix);

    // 4. 处理结果（判断是否为合法数字）
    if (std::isnan(result)) {
        ui->lineEdit->setText("表达式错误");
    } else {
        ui->lineEdit->setText(QString("%1").arg(result, 0, 'g', 10));
    }

    // 清空表达式，准备下一次输入
    expression.clear();
}


void Calculator::on_lb_clicked()
{
    expression +="(";
    ui->lineEdit->setText(expression);
}


void Calculator::on_rb_clicked()
{
    expression +=")";
    ui->lineEdit->setText(expression);
}
