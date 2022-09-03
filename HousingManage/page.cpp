#include "page.h"
#include <QtWidgets>

Page1::Page1(QWidget *parent)
    : QWidget(parent)
{
    QLabel *pageName = new QLabel(tr("Page1"));           //页面设置
    QHBoxLayout *myLayout = new QHBoxLayout;
    myLayout->addWidget(pageName, 1, Qt::AlignCenter);
    setLayout(myLayout);
}

Page2::Page2(QWidget *parent)
    : QWidget(parent)
{
    QLabel *pageName = new QLabel(tr("Page2"));
    QHBoxLayout *myLayout = new QHBoxLayout;
    myLayout->addWidget(pageName, 1, Qt::AlignCenter);
    setLayout(myLayout);
}
