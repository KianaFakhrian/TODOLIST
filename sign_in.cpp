#include "sign_in.h"
#include "ui_sign_in.h"
#include "file_functions.h"
#include <QMessageBox>

Sign_In::Sign_In(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sign_In)
{
    ui->setupUi(this);
}

Sign_In::~Sign_In()
{
    delete ui;
}

void Sign_In::getUsers(QList<User> *Users_list)
{
    users = Users_list ;
}

void Sign_In::on_Sign_in_pushButton_clicked()
{
    QString username = ui->Username_lineEdit->text() ;
    QString password = ui->Password_lineEdit->text() ;
    if(ui->Username_lineEdit->text().isEmpty() || ui->Password_lineEdit->text().isEmpty() ||ui->Email_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"unfilled fields","please fill all the fields") ;
        return ;
    }
    if(!username.contains("Student") && !username.contains("Prof"))
    {
        QMessageBox::warning(this,"wrong username","please choose a username considering conditions") ;
        return ;
    }
    User New_User ;
    New_User.username = username ;
    New_User.password = password ;
    File_Functions::write_Users_To_File("Users.txt",New_User) ;
    emit exit();
}
