#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMainWindow>
#include <user.h>

namespace Ui {
class Sign_In;
}

class Sign_In : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sign_In(QWidget *parent = 0);
    ~Sign_In();
public:
    void getUsers(QList<User>* users_list) ;

private slots:
    void on_Sign_in_pushButton_clicked();
signals:
    void exit() ;
private:
    Ui::Sign_In *ui;
    QList<User>* users ;
};

#endif // SIGN_IN_H
