#include "findfmeberdialog.h"
#include "ui_findfmeberdialog.h"

FindFMeberDialog::FindFMeberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindFMeberDialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());

}

FindFMeberDialog::~FindFMeberDialog()
{
    delete ui;
}

QString FindFMeberDialog::getNumber()
{
    return ui->number_lineEdit->text();
}
