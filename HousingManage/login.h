#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

signals:
    void showmain();
    void visitor();

private slots:
  void on_pB_OK_clicked();
  void on_pB_Exit_clicked();


  void on_pB_Vstr_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
