#include "mainwindow.h"
#include"login.h"
#include <QApplication>
#include<QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("职工管理系统");

    login logIn;
    logIn.setWindowTitle("登入系统");
    //logIn.setWindowIcon(QIcon("/qrc_Icon/Login.png"));
    logIn.show();
    QObject::connect(&logIn, &login::showmain, &w, &MainWindow::receiveLogin);
    QObject::connect(&logIn, &login::visitor, &w, &MainWindow::onlyReadLogin);
    return a.exec();
}
