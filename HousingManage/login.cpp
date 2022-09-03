#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
}

login::~login()
{
    delete ui;
}

void login::on_pB_OK_clicked()
{
    QString Acc = "213213666";
    QString Pass = "20021231";
    if((ui->lineEdit_Login->text() == Acc) && (ui->lineEdit_Pwd->text() == Pass)){
            this->hide();
            emit showmain();
    }
    else if((ui->lineEdit_Login->text() == "") || (ui->lineEdit_Pwd->text() == "")){
            QMessageBox::warning(this, tr("提示"), tr("用户名或密码不能为空"), QMessageBox::Yes);
            ui->lineEdit_Login->clear();
            ui->lineEdit_Login->setFocus();
    }

    else if(ui->lineEdit_Login->text() != Acc){
        QMessageBox::warning(this, tr("提示"), tr("用户名不存在，请重新输入"), QMessageBox::Yes);
        ui->lineEdit_Login->clear();
        ui->lineEdit_Login->setFocus();
    }

    else if((ui->lineEdit_Login->text() == Acc) && (ui->lineEdit_Pwd->text()!= Pass)){
        QMessageBox::warning(this, tr("提示"), tr("用户名密码不匹配，请重新输入"), QMessageBox::Yes);
        ui->lineEdit_Login->setFocus();
    }
}

void login::on_pB_Exit_clicked()
{
    close();
}


void login::on_pB_Vstr_clicked()
{
    this->hide();
    emit visitor();
}
