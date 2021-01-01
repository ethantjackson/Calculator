#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }


class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
      void NumPressed();
      void DecimalPressed();
      void PercentagePressed();
      void MathButtonPressed();
      void EqualButtonPressed();
      void ChangeNumberSign();
      void ClearButtonPressed();
      void AnswerPressed();
};
#endif // CALCULATOR_H
