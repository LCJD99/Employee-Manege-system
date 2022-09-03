#include "mystackwidget.h"
#include "page.h"
#include <QtWidgets>

MYStackedWidget::MYStackedWidget(QWidget *parent)
    : QWidget(parent)
{
    mess = new QPushButton(this);
    mess->setText("显示积分计算器");

    pages = new QStackedWidget;
    pages->addWidget(new Page1);
    pages->addWidget(new Page2);
    QHBoxLayout *myLayout = new QHBoxLayout;
    myLayout->addWidget(pages);
    setLayout(myLayout);
}

void MYStackedWidget::changePage()
{
    curpage++;
    curpage %= 2;
    pages->setCurrentIndex(curpage);


}

MYStackedWidget::~MYStackedWidget()
{

}
