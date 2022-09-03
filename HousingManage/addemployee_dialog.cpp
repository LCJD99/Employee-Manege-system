#include "addemployee_dialog.h"
#include "ui_addemployee_dialog.h"
#include<QDebug>

AddEmployee_Dialog::AddEmployee_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployee_Dialog)
{
    ui->setupUi(this);
}

AddEmployee_Dialog::~AddEmployee_Dialog()
{
    delete ui;
}

QString AddEmployee_Dialog::getNumber()
{
    return ui->numberlineEdit->text();
}

QString AddEmployee_Dialog::getName()
{
    return ui->namelineEdit->text();
}

int AddEmployee_Dialog::getAge()
{
    return ui->age_spinBox->value();
}

QDate AddEmployee_Dialog::getHireDate()
{
    return ui->hireDate_dateEdit->date();
}

int AddEmployee_Dialog::getDegree()
{
   return  ui->degree_comboBox->currentIndex();
}

int AddEmployee_Dialog::getPosition()
{
   return ui->position_comboBox->currentIndex();

}

QString AddEmployee_Dialog::getAddress()
{
    return ui->address_lineEdit->text();
}

float AddEmployee_Dialog::getArea()
{
    return ui->area_doubleSpinBox->value();
}

QVector<Fmember> AddEmployee_Dialog::getFmember()
{
    return tempOne;
}

void AddEmployee_Dialog::on_pushButton_next_clicked()
{
    this->setVisible(false);
    addFMemberDialog *fmemberDialog = new addFMemberDialog(this);
    fmemberDialog->setWindowTitle("添加职工家属");
    int ret = fmemberDialog->exec();
    if(ret == QDialog::Accepted){
        tempOne = fmemberDialog->getFMember();
        accept();
    }

}
