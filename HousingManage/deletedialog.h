#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include<QString>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();

    QString getNumber();

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H
