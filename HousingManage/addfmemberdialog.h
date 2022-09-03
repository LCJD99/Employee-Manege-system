#ifndef ADDFMEMBERDIALOG_H
#define ADDFMEMBERDIALOG_H
#include <QStandardItemModel>
#include <QDialog>
#include<QVector>
#include"fmember.h"

namespace Ui {
class addFMemberDialog;
}

class addFMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFMemberDialog(QWidget *parent = nullptr);
    ~addFMemberDialog();

    void ShowTable(QVector<Fmember>& temp);

    void on_ShowInfotableView_changed();

    QVector<Fmember> getFMember();

private slots:
    void on_Add_pushButton_clicked();

    void on_pushButton_clicked();

    void on_OK_pushButton_clicked();

private:
    QVector<Fmember> tempOne;
    Ui::addFMemberDialog *ui;
    QStandardItemModel * FMemberInforModel;
};

#endif // ADDFMEMBERDIALOG_H
