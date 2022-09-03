#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"login.h"
#include"QDebug"
#include"addemployee_dialog.h"
#include"findbycondition_dialog.h"
#include"findfmeberdialog.h"
#include"login.h"
#include"readonlydelegate.h"
#include"comboxwidgetdelegate.h"
#include"datewidgetdelegate.h"
#include"deletedialog.h"
#include"mystackwidget.h"

#include<QLabel>
#include <QStandardItem>
#include <qvariant.h>
#include <QMessageBox>
#include <QAbstractItemDelegate>
#include <QModelIndex>
#include<QDir>
#include<QFileDialog>
#include<QDebug>
#include <QStandardItem>
#include <qvariant.h>
#include<QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->messstacked->setFrameStyle(QFrame::WinPanel);
    ui->messstacked->setLineWidth(3);
    ui->messstacked->setMidLineWidth(3);
    ui->messstacked->setFrameShadow (QFrame::Raised);
    ui->messstacked->setVisible(false);
    ui->textEdit->setReadOnly(true);

    ui->messLabel->setText("");
    ui->messframe->setFrameStyle(QFrame::WinPanel);
    ui->messframe->setLineWidth(3);
    ui->messframe->setMidLineWidth(3);
    ui->messframe->setFrameShadow (QFrame::Raised);
    ui->messframe->setVisible(false);
    ui->ShowInfotableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ShowInfotableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->ShowInfotableView ->setGeometry(this->x() , ui->menubar->y() , this->width() , this->height());
    EmployeeInforModel = new QStandardItemModel();
    ui->ShowInfotableView->setModel(EmployeeInforModel);
    ui->ShowInfotableView->setAlternatingRowColors(true);
    connect(ui->ShowInfotableView->itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &MainWindow::on_ShowInfotableView_changed);

    ui->actionFindEmployee->setIcon(QIcon(":/file/FindByCondition.png"));
    ui->actionShowMessage->setIcon(QIcon(":/file/ShowAll.png"));
    ui->action_2->setIcon(QIcon(":/file/people.png"));
    ui->actionScore->setIcon(QIcon(":/file/people.png"));
    ui->action->setIcon(QIcon(":/file/people.png"));
    ui->actionAddEmployee->setIcon(QIcon(":/file/Login.png"));
    ui->actionExit->setIcon(QIcon(":/file/CloseDefault.png"));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_iCurTable = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowBasicMessageList()
{
    m_iCurTable = 1;
    ui->cLayout->setStretchFactor(ui->ShowInfotableView,3);
    ui->cLayout->setStretchFactor(ui->messframe,2);
    ui->messframe->setVisible(true);
    ui->messstacked->setVisible(false);

    EmployeeInforModel->clear();
    EmployeeInforModel->setColumnCount(9);
    QStringList templist;
    templist.append("工号");
    templist.append("姓名");
    templist.append("年龄");
    templist.append("入职日期");
    templist.append("学位");
    templist.append("职称");
    templist.append("住房面积");
    templist.append("住址");
    templist.append("家庭成员数");
    EmployeeInforModel->setHorizontalHeaderLabels(templist);
    int RowCnt = m_InfoTable.GetEmployeeNum();
    qDebug() << "RowCnt" << RowCnt;
    EmployeeInforModel->setRowCount(RowCnt);

    ComBoxWidgetDelegate *PositionDialegate = new ComBoxWidgetDelegate();
    PositionDialegate->insertCoBData("教授");
    PositionDialegate->insertCoBData("副教授");
    PositionDialegate->insertCoBData("讲师");
    PositionDialegate->insertCoBData("助教");
    for(int i = 0 ; i < 9 ; ++i){
        ui->ShowInfotableView->setItemDelegateForColumn(i,ui->ShowInfotableView->itemDelegate() );
    }

    ui->ShowInfotableView->setItemDelegateForColumn(5,PositionDialegate);
    connect(PositionDialegate ,
            &ComBoxWidgetDelegate::OnEmitCurrentIndexChangeSignal,
            this,
            &MainWindow::on_ShowInfotableView_changed);

    ComBoxWidgetDelegate *DegreeDialegate  = new ComBoxWidgetDelegate();
    DegreeDialegate->insertCoBData("高中");
    DegreeDialegate->insertCoBData("本科");
    DegreeDialegate->insertCoBData("硕士");
    DegreeDialegate->insertCoBData("博士");
    ui->ShowInfotableView->setItemDelegateForColumn(4,DegreeDialegate);
    connect(DegreeDialegate ,
            &ComBoxWidgetDelegate::OnEmitCurrentIndexChangeSignal,
            this,
            &MainWindow::on_ShowInfotableView_changed);

    DateWidgetDelegate *HireDateDialegate = new DateWidgetDelegate();
    ui->ShowInfotableView->setItemDelegateForColumn(3,HireDateDialegate);

    connect(HireDateDialegate ,
            &DateWidgetDelegate::OnEmitCurrentIndexChangeSignal,
            this,
            &MainWindow::on_ShowInfotableView_changed);

    QStandardItem * aTempItem;
    QString tempStr;
    for(int i = 0 ; i < RowCnt ; ++i){
        Employee tempemployee = m_InfoTable.GetEmployee(i);

        tempStr = tempemployee.WorkerNumber;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 0, aTempItem);

        tempStr = tempemployee.Name;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 1, aTempItem);
        qDebug() << "name" << tempStr;
        tempStr = QString::number(tempemployee.age);
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 2, aTempItem);

        tempStr = tempemployee.hireDate.toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 3, aTempItem);


        tempStr = tempemployee.getDegree();
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 4, aTempItem);

        tempStr = tempemployee.getPosition();
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 5, aTempItem);

        tempStr = QString::number(tempemployee.area);
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 6, aTempItem);

        tempStr = tempemployee.address;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 7, aTempItem);

        tempStr = QString::number(tempemployee.familyMember.size());
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 8, aTempItem);
    }
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(8, readOnlyDelegate);
    if(Authority == false){
        for(int i = 1 ; i <= 8 ; ++i)
            ui->ShowInfotableView->setItemDelegateForColumn(i, readOnlyDelegate);
    }

}

void MainWindow::ShowFmemberList(int t)
{

    ui->messframe->setVisible(false);
    ui->messstacked->setVisible(false);
    if(t == -1) {
         QMessageBox::warning(this, tr("提示"), tr("未查找到该工号"), QMessageBox::Yes);
    }
    else{

        m_iCurTable = 2;
        //qDebug() << "Fmember";
        EmployeeInforModel->clear();
        EmployeeInforModel->setColumnCount(4);
        for(int i = 0 ; i < 4 ; ++i){
            ui->ShowInfotableView->setItemDelegateForColumn(i,ui->ShowInfotableView->itemDelegate() );
        }
        ComBoxWidgetDelegate *SexDialegate = new ComBoxWidgetDelegate();
        SexDialegate->insertCoBData("男");
        SexDialegate->insertCoBData("女");
        ui->ShowInfotableView->setItemDelegateForColumn(1,SexDialegate);
        connect(SexDialegate ,
                &ComBoxWidgetDelegate::OnEmitCurrentIndexChangeSignal,
                this,
                &MainWindow::on_ShowInfotableView_changed);

        QStringList templist;
        templist.append("姓名");
        templist.append("性别");
        templist.append("年龄");
        templist.append("称谓关系");
        EmployeeInforModel->setHorizontalHeaderLabels(templist);
        QVector<Fmember> temps = m_InfoTable.GetEmployee(t).familyMember;
        nowone = t;
        int RowCnt = temps.size();
        //qDebug() << "RowCnt" << RowCnt;
        EmployeeInforModel->setRowCount(RowCnt);
        //qDebug() << tempStr;
        QStandardItem * aTempItem;
        QString tempStr;
        for(int i = 0 ; i < RowCnt ; ++i){
            Fmember tempF = temps[i];
            tempStr = tempF.name;
            aTempItem = new QStandardItem(tempStr);
            EmployeeInforModel->setItem(i, 0, aTempItem);
            //qDebug() << tempStr;
            tempStr = tempF.getSex();
            aTempItem = new QStandardItem(tempStr);
            EmployeeInforModel->setItem(i, 1, aTempItem);
            //qDebug() << tempStr;
            tempStr = QString::number(tempF.age);
            aTempItem = new QStandardItem(tempStr);
            EmployeeInforModel->setItem(i, 2, aTempItem);
            //qDebug() << tempStr;
            tempStr = tempF.relationship;
            aTempItem = new QStandardItem(tempStr);
            EmployeeInforModel->setItem(i, 3, aTempItem);
            //qDebug() << tempStr;
        }

    }
}

void MainWindow::ShowRankList()
{
    ui->messframe->setVisible(false);
    ui->cLayout->setStretchFactor(ui->ShowInfotableView,3);
    ui->cLayout->setStretchFactor(ui->messstacked,2);
    ui->messstacked->setVisible(true);



    m_InfoTable.CalculateRank();
    m_iCurTable = 3;
    EmployeeInforModel->clear();
    EmployeeInforModel->setColumnCount(4);


    QStringList templist;
    templist << "工号" << "姓名" << "积分" <<"排名";
    EmployeeInforModel->setHorizontalHeaderLabels(templist);
    int RowCnt = m_InfoTable.GetEmployeeNum();
    EmployeeInforModel->setRowCount(RowCnt);
    QStandardItem * aTempItem;
    QString tempStr;

    for(int i = 0 ; i < RowCnt ; ++i){
        Employee tempF = m_InfoTable.GetEmployee(m_InfoTable.RankMap[m_InfoTable.Ranks[i]]);
        qDebug() << "Rank" << tempF.rank;
        tempStr = tempF.WorkerNumber;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 0, aTempItem);

        tempStr = tempF.Name;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 1, aTempItem);

        tempStr = QString::number(tempF.intergral,'f',2);
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 2, aTempItem);

        tempStr = QString::number(tempF.rank);
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 3, aTempItem);
    }
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(3, readOnlyDelegate);
}

void MainWindow::ShowFindByConditions(QVector<int> index)
{
    ui->messframe->setVisible(false);
    ui->messstacked->setVisible(false);
    m_iCurTable = 4;
    EmployeeInforModel->clear();
    EmployeeInforModel->setColumnCount(9);
    for(int i = 0 ; i < 9 ; ++i){
        ui->ShowInfotableView->setItemDelegateForColumn(i,ui->ShowInfotableView->itemDelegate() );
    }
    QStringList templist;
    templist.append("工号");
    templist.append("姓名");
    templist.append("年龄");
    templist.append("入职日期");
    templist.append("学位");
    templist.append("职称");
    templist.append("住房面积");
    templist.append("住址");
    templist.append("家庭成员数");
    EmployeeInforModel->setHorizontalHeaderLabels(templist);
    int RowCnt = index.size();
    //qDebug() << "RowCnt" << RowCnt;
    EmployeeInforModel->setRowCount(RowCnt);
    ComBoxWidgetDelegate *PositionDialegate = new ComBoxWidgetDelegate();
    PositionDialegate->insertCoBData("教授");
    PositionDialegate->insertCoBData("副教授");
    PositionDialegate->insertCoBData("讲师");
    PositionDialegate->insertCoBData("助教");
    ui->ShowInfotableView->setItemDelegateForColumn(5,PositionDialegate);
    connect(PositionDialegate ,
            &ComBoxWidgetDelegate::OnEmitCurrentIndexChangeSignal,
            this,
            &MainWindow::on_ShowInfotableView_changed);

    ComBoxWidgetDelegate *DegreeDialegate  = new ComBoxWidgetDelegate();
    DegreeDialegate->insertCoBData("高中");
    DegreeDialegate->insertCoBData("本科");
    DegreeDialegate->insertCoBData("硕士");
    DegreeDialegate->insertCoBData("博士");
    ui->ShowInfotableView->setItemDelegateForColumn(4,DegreeDialegate);
    connect(DegreeDialegate ,
            &ComBoxWidgetDelegate::OnEmitCurrentIndexChangeSignal,
            this,
            &MainWindow::on_ShowInfotableView_changed);

    QStandardItem * aTempItem;
    QString tempStr;
    for(int i = 0 ; i < RowCnt ; ++i){
        Employee tempemployee = m_InfoTable.GetEmployee(index[i]);

        tempStr = tempemployee.WorkerNumber;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 0, aTempItem);

        tempStr = tempemployee.Name;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 1, aTempItem);
        //qDebug() << "name" << tempStr;
        tempStr = QString::number(tempemployee.age);
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 2, aTempItem);

        tempStr = tempemployee.hireDate.toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 3, aTempItem);

        tempStr = tempemployee.getDegree();
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 4, aTempItem);

        tempStr = tempemployee.getPosition();
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 5, aTempItem);

        tempStr = QString::number(tempemployee.area);
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 6, aTempItem);

        tempStr = tempemployee.address;
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 7, aTempItem);

        tempStr = QString::number(tempemployee.familyMember.size());
        aTempItem = new QStandardItem(tempStr);
        EmployeeInforModel->setItem(i, 8, aTempItem);
    }
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(8, readOnlyDelegate);
    if(Authority == false){
        for(int i = 1 ; i <= 8 ; ++i)
            ui->ShowInfotableView->setItemDelegateForColumn(i, readOnlyDelegate);
    }
}

void MainWindow::showLoginMessageBox()
{
    QMessageBox::warning(this, tr("提示"), tr("游客模式无权限执行该操作"), QMessageBox::Yes);
}

void MainWindow::receiveLogin()
{
    qDebug() << "true";
    Authority = true;
    show();
}

void MainWindow::onlyReadLogin()
{
    //qDebug() << "zheli";
    Authority =false;
    show();
}


void MainWindow::on_actionFileOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    m_InfoTable.ReadEmployeeFromFile(aFileName);
}

void MainWindow::on_actionFileSave_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;

    m_InfoTable.SaveEmployeeToFile(aFileName);
}

void MainWindow::on_actionAddEmployee_triggered()
{
    if(Authority == false){
        showLoginMessageBox();
        return;
    }
    AddEmployee_Dialog dlgAdd(this);
    dlgAdd.setWindowTitle("添加职工界面");
    int ret = dlgAdd.exec();
    if(ret == QDialog::Accepted){
        Employee tempEmployee;
        tempEmployee.WorkerNumber = dlgAdd.getNumber();
        //qDebug() << tempEmployee.WorkerNumber;
        tempEmployee.Name = dlgAdd.getName();
        //qDebug() << tempEmployee.Name;
        tempEmployee.age = dlgAdd.getAge();
        tempEmployee.hireDate = dlgAdd.getHireDate();
        tempEmployee.setDegree(dlgAdd.getDegree());
        tempEmployee.setPosition(dlgAdd.getPosition());
        tempEmployee.area = dlgAdd.getArea();
        tempEmployee.address = dlgAdd.getAddress();
        tempEmployee.familyMember = dlgAdd.getFmember();
        m_InfoTable.AddEmployee(tempEmployee);
        ShowBasicMessageList();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_ShowInfotableView_changed()
{
    //qDebug() << "changed";
    QModelIndex index = ui->ShowInfotableView->currentIndex();
    int iR = index.row();
    int iC = index.column();

    QVariant data;

   if(m_iCurTable == 1 || m_iCurTable == 4){
       data = EmployeeInforModel->data(index);
       Employee & employee = m_InfoTable.GetEmployee(iR);
       switch(iC){
       case 0:
           employee.WorkerNumber = data.toString();
           break;
       case 1:
           employee.Name = data.toString();
           //qDebug() << data.toString();
           break;
       case 2:
           employee.age = data.toInt();
           break;
       case 3:
           qDebug() << data.toString();
           employee.hireDate = QDate::fromString(data.toString(),"yyyy-MM-dd");
           break;
       case 4:
           employee.setDegree(data.toString());
           break;
       case 5:
           employee.setPosition(data.toString());
           break;
       case 6:
           employee.area = data.toFloat();
           break;
       case 7:
           employee.address = data.toString();
           break;
       default:
           break;

       }
   }
   else if(m_iCurTable == 2){
       data = EmployeeInforModel->data(index);
       Employee &  temp  = m_InfoTable.GetEmployee(nowone);
       switch (iC) {
       case 0:
           temp.familyMember[iR].name = data.toString();
           break;
       case 1:
           temp.familyMember[iR].setSex(data.toString());
           break;
       case 2:
           temp.familyMember[iR].age = data.toInt();
           break;
       case 3:
           temp.familyMember[iR].relationship = data.toString();
       default:
           break;
       }
   }
}

void MainWindow::on_actionShowMessage_triggered()
{
    ShowBasicMessageList();
}

void MainWindow::on_action_triggered()
{
    FindFMeberDialog* findFmemberdialog = new FindFMeberDialog(this);
    findFmemberdialog->setWindowTitle("查找指定员工的家属列表");
    int ret = findFmemberdialog->exec();
    int m = -1;
    if(ret == QDialog::Accepted){
        int size = m_InfoTable.GetEmployeeNum();
        for(int i  = 0 ; i < size ; ++i){
            Employee temp = m_InfoTable.GetEmployee(i);
            if(temp.WorkerNumber == findFmemberdialog->getNumber()){
                m = i;
                break;
            }
        }
        ShowFmemberList(m);
    }

}

void MainWindow::on_actionFindEmployee_triggered()
{
    FindByCondition_Dialog * findbycondition_dialog = new FindByCondition_Dialog(this);
    findbycondition_dialog->setWindowTitle("按条件查找职工");
    int ret = findbycondition_dialog->exec();
    QVector<int> tempList;
    if(ret == QDialog::Accepted){
        int size = m_InfoTable.GetEmployeeNum();
        for(int i = 0 ; i < size ; ++i){
            Employee temp = m_InfoTable.GetEmployee(i);
            if(findbycondition_dialog->Numbercheck()){
                if(temp.WorkerNumber != findbycondition_dialog->GetNumber()) continue;
            }
            if(findbycondition_dialog->Namecheck()){
                if(temp.Name != findbycondition_dialog->GetName()) continue;
            }
            if(findbycondition_dialog->Agecheck()){
               int age = findbycondition_dialog->getAge() + 1;
               age *= 10;
               if(temp.age < age || temp.age > age + 9) continue;
            }
            if(findbycondition_dialog->Degreecheck()){
                if(temp.getDegree() != findbycondition_dialog->getDegree()) continue;
            }
            if(findbycondition_dialog->Positioncheck()){
                if(temp.getPosition() != findbycondition_dialog->getPosition()) continue;
            }
            tempList.push_back(i);
        }
        ShowFindByConditions(tempList);
    }
}

void MainWindow::on_actionScore_triggered()
{
    ShowRankList();
}

void MainWindow::on_actionAccontIn_triggered()
{
    if(Authority != false){
        QMessageBox::information(this, tr("消息"), tr("已登入账户"), QMessageBox::Yes);
        return;
    }
    login logIn;
    logIn.setWindowTitle("登入系统");
    logIn.exec();
    Authority = true;
    connect(&logIn, &login::showmain, this, &MainWindow::receiveLogin);
    connect(&logIn, &login::visitor, this, &MainWindow::onlyReadLogin);
}

void MainWindow::on_actionAcoontOut_triggered()
{
    if(Authority == false){
        QMessageBox::information(this, tr("提示"), tr("未登入管理员模式"), QMessageBox::Yes);
        return;
    }
    int ret = QMessageBox::question(this,tr("提示"),tr("是否退出管理员模式"));
    if(ret == QMessageBox::Yes){
        //qDebug() << "false";
        Authority = false;
    }

}

void MainWindow::on_action_2_triggered()
{
    if(Authority == false){
        QMessageBox::information(this, tr("提示"), tr("未登入管理员模式"), QMessageBox::Yes);
        return;
    }
    DeleteDialog * del = new DeleteDialog(this);
    del->setWindowTitle("删除职工数据");
    int ret = del->exec();
    if(ret == QDialog::Accepted){
        QString s = del->getNumber();
        int size = m_InfoTable.GetEmployeeNum();
        for(int i = 0 ; i <size ; ++i){
            if(m_InfoTable.m_employees[i].WorkerNumber == s){
                m_InfoTable.m_employees.erase( m_InfoTable.m_employees.begin() + i ,  m_InfoTable.m_employees.begin() + i +1);
                return;
            }
        }
        QMessageBox::information(this, tr("提示"), tr("未找到该职工"), QMessageBox::Yes);
    }
}

void MainWindow::on_ShowInfotableView_clicked(const QModelIndex &index)
{
    if(m_iCurTable == 1 ){
       int i = index.row();
        if( m_InfoTable.m_employees.size() > i){
            ui->cLayout->setStretchFactor(ui->ShowInfotableView,3);
            ui->cLayout->setStretchFactor(ui->messframe,2);
            QString temp;
            QString text;
            Employee employee = m_InfoTable.m_employees[i];
            temp = "工号:" + employee.WorkerNumber;
            text += temp + '\n';

            temp = "姓名:" + employee.Name;
            text += temp + '\n';

            temp = "年龄:" + QString::number(employee.age);
            text += temp + '\n';

            temp = "就职日期:" + employee.hireDate.toString("yyyy-MM-dd");
            text += temp + '\n';

            temp = "学位:" + employee.getDegree();
            text += temp + '\n';

            temp = "职称:" + employee.getPosition();
            text += temp + '\n';

            temp = "住房大小:" + QString::number(employee.area) + "平方米";
            text += temp + '\n';

            temp = "地址:" + employee.address;
            text += temp + '\n';
            ui->messLabel->setText(text);
            QFont te;
            te.setPointSize(20);
            ui->messLabel->setFont(te);
        }
        else ui->messLabel->setText("");
    }

}


void MainWindow::on_last_pushButton_clicked()
{
    ui->messstacked->setCurrentIndex(0);
}

void MainWindow::on_next_pushButton_clicked()
{
    ui->messstacked->setCurrentIndex(1);
}

void MainWindow::on_caculatepushButton_clicked()
{
    Employee tempEmployee;
    tempEmployee.age = ui->age_spinBox->text().toInt();
    tempEmployee.hireDate = ui->hireDate_dateEdit->date();
    tempEmployee.setDegree(ui->degree_comboBox->currentIndex());
    tempEmployee.setPosition(ui->position_comboBox->currentIndex());
    tempEmployee.area = ui->area_doubleSpinBox->text().toDouble();
    tempEmployee.familyMember.resize(ui->spinBox->text().toInt());
    tempEmployee.CaculateIntergral();
    QString temp = "总积分为：" + QString::number(tempEmployee.intergral);
    QFont te;
    te.setPointSize(20);
    ui->score_label->setFont(te);
    ui->score_label->setText(temp);

}
