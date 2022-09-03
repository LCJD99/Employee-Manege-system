#pragma once

#include <QItemDelegate>

class ComBoxWidgetDelegate : public QItemDelegate {
    Q_OBJECT
public:
    ComBoxWidgetDelegate(QItemDelegate *parent = nullptr);
    ComBoxWidgetDelegate(QStringList list, QItemDelegate *parent = nullptr);
    ~ComBoxWidgetDelegate();



    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    QString getCurrentComboBoxData(int index);

    void insertCoBData(QString str);

    void removeCobData(QString str);

signals:
    void OnEmitCurrentIndexChangeSignal() const;
private:
    QStringList m_comboBoxList;
};
