#ifndef ADDEMPLOYEE_DIALOG_H
#define ADDEMPLOYEE_DIALOG_H

#include <QDialog>
#include"employee.h"
#include"addfmemberdialog.h"

namespace Ui {
class AddEmployee_Dialog;
}

class AddEmployee_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployee_Dialog(QWidget *parent = nullptr);
    ~AddEmployee_Dialog();

    QString getNumber();
    QString getName();
    int getAge();
    QDate getHireDate();
    int getDegree();
    int getPosition();
    QString getAddress();
    float getArea();
    QVector<Fmember> getFmember();


private slots:
    void on_pushButton_next_clicked();

private:
    Ui::AddEmployee_Dialog *ui;
    QVector<Fmember> tempOne;
};

#endif // ADDEMPLOYEE_DIALOG_H
