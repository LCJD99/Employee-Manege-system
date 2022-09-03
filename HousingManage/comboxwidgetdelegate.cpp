#include "comboxwidgetdelegate.h"

#include <QComboBox>

ComBoxWidgetDelegate::ComBoxWidgetDelegate(QItemDelegate *parent) : QItemDelegate(parent) {
    this->m_comboBoxList << "";
}

ComBoxWidgetDelegate::ComBoxWidgetDelegate(QStringList list, QItemDelegate *parent) :QItemDelegate(parent) {
    this->m_comboBoxList = list;
}

ComBoxWidgetDelegate::~ComBoxWidgetDelegate() {

}

QWidget *ComBoxWidgetDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    QComboBox *editor = new QComboBox(parent);

    return editor;
}


void ComBoxWidgetDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    QComboBox *cob = static_cast<QComboBox *>(editor);
    cob->addItems(m_comboBoxList);
}


void ComBoxWidgetDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    editor->setGeometry(option.rect);
}


void ComBoxWidgetDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *comboBox = static_cast<QComboBox *>(editor);

    model->setData(index, comboBox->currentText());
    OnEmitCurrentIndexChangeSignal();
}


QString ComBoxWidgetDelegate::getCurrentComboBoxData(int index) {
    return this->m_comboBoxList.at(index);
}


void ComBoxWidgetDelegate::insertCoBData(QString str) {
    this->m_comboBoxList.append(str);
}


void ComBoxWidgetDelegate::removeCobData(QString str) {
    for (int i = 0; i < this->m_comboBoxList.size(); i++) {
        if (str == this->m_comboBoxList[i]) {
            this->m_comboBoxList.removeAt(i);
            return;
        }
    }
}
