#include "datewidgetdelegate.h"

#include <QDateEdit>

DateWidgetDelegate::DateWidgetDelegate(QItemDelegate *parent) : QItemDelegate(parent) {}


DateWidgetDelegate::~DateWidgetDelegate() {

}

QWidget *DateWidgetDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    QDateTimeEdit *editor = new QDateTimeEdit(parent);
    editor->setDisplayFormat("yyyy-MM-dd");
    return editor;
}


void DateWidgetDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QDateEdit *timeEd = static_cast<QDateEdit *>(editor);
    QString s = index.model()->data(index,Qt::EditRole).toString();
    timeEd->setDate(QDate::fromString(s,"yyyy-MM-dd"));
}

void DateWidgetDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    editor->setGeometry(option.rect);
}

void DateWidgetDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QDateEdit *datetimeedit = static_cast<QDateEdit *>(editor);
    QString s =  datetimeedit->date().toString("yyyy-MM-dd");
    model->setData(index,s);
    emit OnEmitCurrentIndexChangeSignal();
}









