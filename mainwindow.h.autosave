#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "user.h"
#include "professor_panel.h"
#include "student_panel.h"
#include "sign_in.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readUsers() ;
    void readTasks() ;
    bool valid_User_Pass(const QString&,const QString&) ;
    bool Is_User_Student() ;
    bool Is_User_Professor() ;

private slots:
    void on_Login_PushB_clicked();

    void on_sign_in_PushB_clicked();

private:
    Ui::MainWindow *ui;
    Professor_Panel* professor_panel ;
    Student_Panel* student_panel ;
    Sign_In* sign_in ;
    QString username ;
    QString password ;
    QList<User> users_list ;
};

#endif // MAINWINDOW_H
