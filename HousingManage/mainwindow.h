#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QStandardItemModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include"employeetable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ShowBasicMessageList();  //1

    void ShowFmemberList(int i);       //2

    void ShowRankList();          //3

    void ShowFindByConditions(QVector<int> inde);  //4

    void showLoginMessageBox();



public slots:
    void receiveLogin();
    void onlyReadLogin();
private slots:
    void on_actionFileOpen_triggered();

    void on_actionFileSave_triggered();

    void on_actionAddEmployee_triggered();

    void on_actionExit_triggered();

    void on_ShowInfotableView_changed();

    void on_actionShowMessage_triggered();

    void on_action_triggered();

    void on_actionFindEmployee_triggered();

    void on_actionScore_triggered();

    void on_actionAccontIn_triggered();

    void on_actionAcoontOut_triggered();

    void on_action_2_triggered();

    void on_ShowInfotableView_clicked(const QModelIndex &index);

    void on_last_pushButton_clicked();

    void on_next_pushButton_clicked();

    void on_caculatepushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel * EmployeeInforModel;
    EmployeeTable m_InfoTable;
    int m_iCurTable;

    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    DataTable m_dataTable;
private:
    bool Authority;
    int nowone = -1;
};
#endif // MAINWINDOW_H
