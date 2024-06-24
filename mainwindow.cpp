#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "file_functions.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readUsers();
    readTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readTasks()
{
    File_Functions::read_Tasks_From_File("Tasks.txt",users_list) ;
}

void MainWindow::readUsers()
{
    File_Functions::read_Users_From_File("Users.txt",users_list) ;
}

void MainWindow::on_Login_PushB_clicked()
{
    if(ui->UserName_LineEdit->text().isEmpty() || ui->Password_LineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"invalid username or password","Please Enter right username and password") ;
        return ;
    }
    QString username = ui->UserName_LineEdit->text() ;
    QString password = ui->Password_LineEdit->text() ;
    if(!valid_User_Pass(username,password))
    {
        return ;
    }
    if(Is_User_Student())
    {
        hide() ;
        student_panel = new Student_Panel(this) ;
        student_panel->get_Users(&users_list);
        student_panel->show();
    }
    else if(Is_User_Professor())
    {
        hide() ;
        professor_panel = new Professor_Panel(this) ;
        professor_panel->get_Users(&users_list) ;
        professor_panel->show();
    }
}
bool MainWindow::valid_User_Pass(const QString& Username,const QString& Password)
{
    for(User &users:users_list)
    {
        if(users.username == Username && users.password == Password)
        {
            username = users.username ;
            password = users.password ;
            return true ;
        }
    }
    QMessageBox::warning(this,"invalid username or password","Please Enter right username and password") ;
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
    QStatusBar*statusBar = new QStatusBar(this) ;
    setStatusBar(statusBar);
    statusBar->showMessage("asfasdfasdfaf");
}
