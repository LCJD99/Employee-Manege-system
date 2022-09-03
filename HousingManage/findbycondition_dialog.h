#ifndef FINDBYCONDITION_DIALOG_H
#define FINDBYCONDITION_DIALOG_H

#include <QDialog>

namespace Ui {
class FindByCondition_Dialog;
}

class FindByCondition_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindByCondition_Dialog(QWidget *parent = nullptr);
    ~FindByCondition_Dialog();

    QString GetNumber();
    QString GetName();
    int getAge();
    QString getPosition();
    QString getDegree();

    bool Numbercheck();
    bool Namecheck();
    bool Agecheck();
    bool Positioncheck();
    bool Degreecheck();

private:
    Ui::FindByCondition_Dialog *ui;
};

#endif // FINDBYCONDITION_DIALOG_H
