#include "starred_tasks.h"
#include "ui_starred_tasks.h"
#include <QListWidgetItem>
#include <QDebug>

starred_tasks::starred_tasks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::starred_tasks)
{
    ui->setupUi(this);
}

starred_tasks::~starred_tasks()
{
    delete ui;
}

void starred_tasks::load_starred_tasks()
{
    ui->listWidget->clear();
    Task* task = task_lists.head ;
    while(task != nullptr)
    {
        qDebug() <<task->Star ;
        if(task->Star)
        {
            QListWidgetItem *item = new QListWidgetItem(task->Task_Name) ;
            ui->listWidget->addItem(item);

        }
        task = task->next ;
    }
}

void starred_tasks::get_list(linkedList & list)
{
    task_lists = list ;
}

void starred_tasks::on_close_pushButton_clicked()
{
    this->close() ;
}
