#include "addfmemberdialog.h"
#include "ui_addfmemberdialog.h"
#include <QAbstractItemDelegate>
#include <QStandardItem>
#include<QDebug>
addFMemberDialog::addFMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFMemberDialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    FMemberInforModel = new QStandardItemModel;
    ui->ShowInfotableView->setModel(FMemberInforModel);
    connect(ui->ShowInfotableView->itemDelegate(),&QAbstractItemDelegate::closeEditor,this , &addFMemberDialog::on_ShowInfotableView_changed);
}

addFMemberDialog::~addFMemberDialog()
{
    delete ui;
}

void addFMemberDialog::ShowTable(QVector<Fmember>& temp )
{
    FMemberInforModel->clear();
    FMemberInforModel->setColumnCount(4);

    QStringList tempList;
    tempList.append("姓名");
    tempList.append("性别");
    tempList.append("年龄");
    tempList.append("称谓关系");
    FMemberInforModel->setHorizontalHeaderLabels(tempList);

    int RowCnt = temp.size();
    FMemberInforModel->setRowCount(RowCnt);

    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0 ; i < RowCnt ; ++i){
        tempStr = temp[i].name;
        aTempItem = new QStandardItem(tempStr);
        FMemberInforModel->setItem(i , 0 , aTempItem);

        tempStr = temp[i].getSex();
        aTempItem = new QStandardItem(tempStr);
        FMemberInforModel->setItem(i , 1 , aTempItem);

        tempStr = QString::number(temp[i].age);
        aTempItem = new QStandardItem(tempStr);
        FMemberInforModel->setItem(i , 2 , aTempItem);

        tempStr = temp[i].relationship;
        aTempItem = new QStandardItem(tempStr);
        FMemberInforModel->setItem(i , 3 , aTempItem);
    }
}

void addFMemberDialog::on_ShowInfotableView_changed()
{
    qDebug() << "this";
    QModelIndex index = ui->ShowInfotableView->currentIndex();
    int iR = index.row();
    int iC = index.column();
    QVariant data = FMemberInforModel->data(index); //数据
    switch (iC) {
    case 0:
        tempOne[iR].name = data.toString();
        qDebug() << iR << "  " << data.toString();
        break;
    case 1:
        tempOne[iR].setSex(data.toString());
        break;
    case 2:
        tempOne[iR].age = data.toInt();
        break;
    case 3:
        tempOne[iR].relationship = data.toString();
        break;
    }
}

QVector<Fmember> addFMemberDialog::getFMember()
{
    return tempOne;
}



void addFMemberDialog::on_Add_pushButton_clicked()
{
    Fmember temp;
    tempOne.push_back(temp);
    ShowTable(tempOne);
}

void addFMemberDialog::on_pushButton_clicked()
{
     QModelIndex index = ui->ShowInfotableView->currentIndex();
     tempOne.remove(index.row());
     ShowTable(tempOne);

}

void addFMemberDialog::on_OK_pushButton_clicked()
{

}
