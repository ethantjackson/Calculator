#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
double answer = calcVal;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

bool equalPressed = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; ++i) {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Decimal, SIGNAL(released()), this, SLOT(DecimalPressed()));

    connect(ui->Percentage, SIGNAL(released()), this, SLOT(PercentagePressed()));

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));

    connect(ui->Answer, SIGNAL(released()), this, SLOT(AnswerPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    QRegExp reg("[0-9]*[.][0-9]*");
    if ((displayVal == "0" || displayVal == "")) {
        ui->Display->setText(butVal);
    } else if (equalPressed) {
        ui->Display->setText(butVal);
    } else if (reg.exactMatch(displayVal)) {
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
    }  else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
    equalPressed = false;
}

void Calculator::DecimalPressed() {
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9]*");
    if (reg.exactMatch(displayVal) && !equalPressed) {
        ui->Display->setText(displayVal + ".");
    }
    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0) {
        ui->Display->setText("0.");
    }
}

void Calculator::PercentagePressed() {
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValPercentage = dblDisplayVal / 100;
    ui->Display->setText(QString::number(dblDisplayValPercentage));
    equalPressed = true;
    answer = dblDisplayValPercentage;
}

void Calculator::MathButtonPressed() {
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0) {
        multTrigger = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || divTrigger || multTrigger) {
        if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        } else if (divTrigger) {
            solution = calcVal / dblDisplayVal;
        }
        ui->Display->setText(QString::number(solution));
    }
    answer = solution;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    equalPressed = true;
}

void Calculator::ChangeNumberSign() {
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayVal)) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}

void Calculator::ClearButtonPressed() {
    calcVal = 0.0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    equalPressed = false;
    ui->Display->setText("");
}

void Calculator::AnswerPressed() {
    ui->Display->setText(QString::number(answer));
}
