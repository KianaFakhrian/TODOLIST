#include "notification.h"
#include "ui_notification.h"
#include "file_functions.h"

Notification::Notification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Notification)
{
    ui->setupUi(this);
}

Notification::~Notification()
{
    delete ui;
}

void Notification::get_user(User * user_logged_in)
{
    user = user_logged_in ;
}

void Notification::get_list_name(QString currentList)
{
    list_name = currentList ;
}
void Notification::get_task_name(QString Task_Name)
{
    task_name = Task_Name ;
}

void Notification::get_users(QList<User> * users_list)
{
    users = users_list ;
}

void Notification::update_file()
{
    File_Functions::update_Task_Notification("tasks_file.txt",*users,list_name,task_name,task->notification,user->username) ;
}

void Notification::on_Yes_clicked()
{
    search_Task();
    task->notification = true ;
    update_file();
    emit exit() ;
}
void Notification::on_No_clicked()
{
    search_Task();
    task->notification = false ;
    update_file();
    emit exit() ;
}

void Notification::search_Task()
{
    task = user->list_of_tasks[list_name].head ;
    while(task != nullptr)
    {
        if(task->Task_Name == task_name)
        {
            break ;
        }
        task = task->next ;
    }
}
