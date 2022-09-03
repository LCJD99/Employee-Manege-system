#ifndef MYSTACKEDWIDGET_H
#define MYSTACKEDWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include<QPushButton>

class MYStackedWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton * mess;
    QStackedWidget *pages;
    int curpage;

public:
    MYStackedWidget(QWidget *parent = 0);
    ~MYStackedWidget();

public slots:
    void changePage();
};

#endif // MYSTACKEDWIDGET_H
