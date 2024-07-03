#include "professor_panel.h"
#include "ui_professor_panel.h"
#include "file_functions.h"
#include <QDebug>

Professor_Panel::Professor_Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Professor_Panel)
{
    ui->setupUi(this);
    ui->treeWidget->clear();
//    ui->pushButton_Back_toList->setVisible(false);
    ui->treeWidget->setColumnCount(2);
    connect(ui->treeWidget,&QTreeWidget::itemClicked,this,&Professor_Panel::update_tasks) ;
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Professor_Panel::switch_list);
    connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,this,&Professor_Panel::star_task) ;
}
Professor_Panel::~Professor_Panel()
{
    delete ui;
}

void Professor_Panel::get_Users(QList<User> *Users_List)
{
    users = Users_List ;
}
void Professor_Panel::add_list()
{
    QString list_name = ui->list_name_lineEdit->text() ;
    user->list_of_tasks[list_name] = linkedList() ;
    QListWidgetItem *item = new QListWidgetItem(list_name,ui->listWidget) ;
    ui->listWidget->addItem(item);
    currentList = list_name ;
}
void Professor_Panel::set_User(User *logged_in)
{
    user = logged_in;
    load_list();
}

void Professor_Panel::load_list()
{
    ui->listWidget->clear();
    for(const QString &list_name : user->list_of_tasks.keys())
    {
        QListWidgetItem *item = new QListWidgetItem(list_name) ;
        ui->listWidget->addItem(item);
    }

}

void Professor_Panel::load_tasks()
{

    Task* tmp_task = user->list_of_tasks[currentList].head ;
    while(tmp_task !=nullptr)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget) ;
        item->setText(0,tmp_task->Task_Name);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(0,tmp_task->done ? Qt::Checked : Qt::Unchecked);
        if(tmp_task->Star)
        {
            item->setIcon(0,QIcon("/Users/HP/Downloads/star.png"));
        }
        ui->treeWidget->addTopLevelItem(item);
        add_Child(item,tmp_task->Due_Date,tmp_task->Explanation);

        tmp_task = tmp_task->next;
    }
}
void Professor_Panel::add_Task()
{
    Task task ;
    task.Task_Name = ui->task_name_lineEdit->text() ;
    task.Due_Date = ui->dateTimeEdit->text() ;
    task.Explanation = ui->lineEdit_description->text() ;
    task.done = false ;
    task.Star = false ;
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,task.Task_Name);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(0,Qt::Unchecked);
    user->list_of_tasks[currentList] << task ;
    ui->treeWidget->addTopLevelItem(item);
    File_Functions::write_Tasks_To_File("tasks_file.txt",task,user->username,currentList) ;
    add_Child(item,task.Explanation,task.Due_Date);
}

void Professor_Panel::add_Child(QTreeWidgetItem* parent,QString description,QString due_date)
{
    QTreeWidgetItem* item = new QTreeWidgetItem() ;
    item->setText(0,due_date);
    item->setText(1,description);
    parent->addChild(item);
}

void Professor_Panel::switch_list(QListWidgetItem *item)
{
    currentList= item->text() ;
    ui->treeWidget->clear();
    load_tasks();
//    ui->pushButton_Back_toList->setVisible(true);
}

void Professor_Panel::on_add_task_button_clicked()
{
    add_Task();
    ui->task_name_lineEdit->setText("");
}
void Professor_Panel::on_new_list_Button_clicked()
{
    add_list();
    ui->list_name_lineEdit->setText("");
}
void Professor_Panel::update_tasks(QTreeWidgetItem* item)
{
    QString taskName = item->text(0) ;
    bool done = (item->checkState(0) == Qt::Checked);

    Task *task = user->list_of_tasks[currentList].head;
    while (task != nullptr)
    {
        if (task->Task_Name == taskName)
        {

            task->done = done;
            File_Functions::updateDoneTask("tasks_file.txt",*users,currentList,taskName,done,user->username) ;
            break;

        }
        task = task->next;
    }
}
void Professor_Panel::star_task(QTreeWidgetItem *item)
{
        QString task_name = item->text(0);
        Task* task = user->list_of_tasks[currentList].head ;
        item->setIcon(0,QIcon("/Users/HP/Downloads/star.png"));
        while(task != nullptr)
        {
            if(task->Task_Name == task_name)
            {
                task->Star = true ;
                break ;
            }
            task = task->next ;
        }
        File_Functions::updateStaredTask("tasks_file.txt",*users,currentList,task_name,task->Star,user->username) ;
}


//void Professor_Panel::on_pushButton_Back_toList_clicked()
//{
//    ui->listWidgetTask->hide();
//    ui->pushButton_Back_toList->setVisible(false);
//}
