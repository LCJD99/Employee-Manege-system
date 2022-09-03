#ifndef FINDFMEBERDIALOG_H
#define FINDFMEBERDIALOG_H

#include <QDialog>

namespace Ui {
class FindFMeberDialog;
}

class FindFMeberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindFMeberDialog(QWidget *parent = nullptr);
    ~FindFMeberDialog();

    QString getNumber();

private:
    Ui::FindFMeberDialog *ui;
};

#endif // FINDFMEBERDIALOG_H
