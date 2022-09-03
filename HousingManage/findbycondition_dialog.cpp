#include "findbycondition_dialog.h"
#include "ui_findbycondition_dialog.h"

FindByCondition_Dialog::FindByCondition_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindByCondition_Dialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
}

FindByCondition_Dialog::~FindByCondition_Dialog()
{
    delete ui;
}

QString FindByCondition_Dialog::GetNumber()
{
    return ui->number_lineEdit->text();
}

QString FindByCondition_Dialog::GetName()
{
    return ui->name_lineEdit->text();
}

int FindByCondition_Dialog::getAge()
{
    return ui->age_comboBox->currentIndex();
}

QString FindByCondition_Dialog::getPosition()
{
    return ui->position_comboBox->currentText();
}

QString FindByCondition_Dialog::getDegree()
{
    return ui->degree_comboBox->currentText();
}

bool FindByCondition_Dialog::Numbercheck(){
    return ui->number_heckBox->isChecked();
}
bool FindByCondition_Dialog::Namecheck(){
    return ui->name_checkBox->isChecked();
}
bool FindByCondition_Dialog::Agecheck(){
    return ui->age_checkBox->isChecked();
}
bool FindByCondition_Dialog::Positioncheck(){
    return ui->position_checkBox -> isChecked();
}
bool FindByCondition_Dialog::Degreecheck(){
     return ui->degree_checkBox -> isChecked();
}

