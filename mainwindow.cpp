#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "file_functions.h"
#include "QSidePanel/PanelLeftSide.hpp"
#include "QSidePanel/math.hpp"

#include <QScroller>

#include "QSidePanel/side_panel_helpers.hpp"

#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->invalid_password->hide();
    ui->invalid_username->hide();
    readUsers();
    readTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readTasks()
{
    File_Functions::read_Tasks_From_File("tasks_file.txt",users_list) ;
}

void MainWindow::readUsers()
{
    File_Functions::read_Users_From_File("Users.txt",users_list) ;
}
void MainWindow::on_Login_PushB_clicked()
{
    student_panel = new Student_Panel(this) ;
    professor_panel = new Professor_Panel(this) ;
    readUsers();
    if(ui->UserName_LineEdit->text().isEmpty())
    {
        ui->invalid_username->setVisible(true);
        ui->invalid_username->setText("Please Fill The Username Field");
        return ;
    }
    else if(ui->Password_LineEdit->text().isEmpty())
    {
        ui->invalid_password->setVisible(true);
        ui->invalid_password->setText("Please Fill The Password Field");
        return ;
    }
    QString username = ui->UserName_LineEdit->text() ;
    QString password = ui->Password_LineEdit->text() ;
    if(!valid_User(username))
    {
        ui->invalid_username->setVisible(true);
        ui->invalid_username->setText("Incorrect Username");
        return ;
    }
    if(!valid_Pass(username,password))
    {
        ui->invalid_username->hide();
        ui->invalid_password->setVisible(true);
        ui->invalid_password->setText("Incorrect Password");
        return ;
    }
    if(Is_User_Student())
    {
        hide() ;
        student_panel->get_Users(&users_list);
        student_panel->showing_notif();
        student_panel->show();
    }
    else if(Is_User_Professor())
    {
        hide() ;
        professor_panel->get_Users(&users_list) ;
        professor_panel->showing_notif();
        professor_panel->show();
    }
}
bool MainWindow::valid_Pass(const QString& Username,const QString& Password)
{
    for(User &users:users_list)
    {
        if(users.username == Username && users.password == Password)
        {
            username = users.username ;
            password = users.password ;
            student_panel->set_username_label(users.username);
            professor_panel->set_username_label(users.username);
            professor_panel->set_User(&users) ;
            student_panel->set_User(&users);
            return true ;
        }
    }
    return false ;
}
bool MainWindow::valid_User(const QString& Username)
{
    for(User &users:users_list)
    {
        if(users.username == Username)
        {
            return true ;
        }
    }
    return false ;
}

bool MainWindow::Is_User_Student()
{
    if(username.contains("Student"))
    {
        return true ;
    }
    return false ;
}

bool MainWindow::Is_User_Professor()
{
    if(username.contains("Prof"))
    {
        return true ;
    }
    return false ;
}
void MainWindow::on_sign_in_PushB_clicked()
{
    hide() ;
    sign_in = new Sign_In(this) ;
    sign_in->getUsers(&users_list);
    connect(sign_in,&Sign_In::exit,this,&MainWindow::close_signin) ;
    sign_in->show();
}

void MainWindow::close_signin()
{
    sign_in->close() ;
    this->show();
}
