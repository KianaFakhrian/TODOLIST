#include "professor_panel.h"
#include "ui_professor_panel.h"
#include "file_functions.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QSystemTrayIcon>
#include <QDate>
#include <map>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QTextCursor>
#include <QBrush>
Professor_Panel::Professor_Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Professor_Panel)
{
    ui->setupUi(this);

    ui->ThemecomboBox->addItem("Light Theme");
    ui->ThemecomboBox->addItem("Dark Theme");
    connect(ui->ThemecomboBox,&QComboBox::currentTextChanged,this,&Professor_Panel::changeTheme) ;

    ui->list_color_comboBox->addItem("Red");
    changeTheme("Light Theme") ;

    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(2);

    connect(ui->treeWidget,&QTreeWidget::itemClicked,this,&Professor_Panel::update_tasks) ;
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Professor_Panel::switch_list);
    connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,this,&Professor_Panel::star_task) ;

    trayIcon = new QSystemTrayIcon(QIcon("/Users/HP/Documents/ToDoList/icons8-notification-64.png")) ;
    trayIcon->show();

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
    user->list_of_tasks.insert(std::make_pair(list_name,linkedList())) ;
    QListWidgetItem *item = new QListWidgetItem(list_name,ui->listWidget) ;
    QString list_color = ui->list_color_comboBox->currentText() ;
    QColor color ;
    if(list_color == "Red")
    {
        color = Qt::red ;
    }
    change_List_Color(item,color) ;
    ui->listWidget->addItem(item) ;
    currentList = list_name ;
}
void Professor_Panel::change_List_Color(QListWidgetItem* item,const QColor& backGround)
{
    QBrush backgroundBrush(backGround) ;
    item->setBackground(backgroundBrush);
}
void Professor_Panel::set_User(User *logged_in)
{
    user = logged_in;
    load_list();
}

void Professor_Panel::load_list()
{
    ui->listWidget->clear();
    QString list_name ;
    for(std::pair<QString,linkedList> Pair : user->list_of_tasks)
    {
        list_name = Pair.first ;
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
            item->setIcon(0,QIcon("/Users/HP/Documents/ToDoList/star.png"));
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
    task.notification = false ;
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

void Professor_Panel::loadTheme(const QString & themeFile)
{
    QFile file(themeFile);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

void Professor_Panel::switch_list(QListWidgetItem *item)
{
    currentList = item->text() ;
    ui->treeWidget->clear();
    load_tasks();
//    ui->pushButton_Back_toList->setVisible(true);
}

void Professor_Panel::on_add_task_button_clicked()
{
    add_Task();
    notification = new Notification(this) ;
    notification->get_user(user);
    notification->get_task_name(ui->task_name_lineEdit->text() );
    notification->get_list_name(currentList);
    notification->get_users(users);
    connect(notification,&Notification::exit,this,&Professor_Panel::close_notif_Page) ;
    notification->show();
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
        item->setIcon(0,QIcon("/Users/HP/Documents/ToDoList/star.png"));
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

void Professor_Panel::changeTheme(const QString & theme)
{
    if(theme == "Dark Theme")
        loadTheme(":/new/prefix1/darkTheme.qss");
    else if(theme == "Light Theme")
        loadTheme(":/new/prefix1/Light Theme.qss");
}

void Professor_Panel::show_notification(const QString &title, const QString &message)
{
    trayIcon->showMessage(title,message,QSystemTrayIcon::NoIcon,3000);
}


void Professor_Panel::getPDF(const QString & List_name)
{
    Task* task = user->list_of_tasks[List_name].head ;
    QTextDocument document ;
    QString html = "<h1>Task List: " + List_name + "</h1><ul>" ;
    while(task != nullptr)
    {
        QString star = task->Star ? "<img src='/Users/HP/Documents/ToDoList/star.png' width='16' height='16'>"  : "";
        QString done = task->done ? "<img src='/Users/HP/Documents/ToDoList/checkmark.png' width = '16' height = '16'>"
                                  : "<img src = 'C:/Users/HP/Documents/ToDoList/crossed.png' width = '16' height = '16'>" ;
        html += "<li>" + task->Task_Name + " - " + task->Due_Date + " "
                + done + " " + star + "<br>" + task->Explanation +"</li>" ;
        task = task->next ;
    }
    html += "</ul>" ;
    document.setHtml(html);
    QString filePath = QFileDialog::getSaveFileName(this,"Save PDF","","*.pdf") ;
    if(filePath.isEmpty())
        return ;
    QPrinter printer(QPrinter::PrinterResolution) ;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    document.print(&printer) ;

}

void Professor_Panel::showing_notif()
{
    QDate currentDate = QDate::currentDate() ;
    QString Date = currentDate.toString("M/d/yyyy") ;
    qDebug() << Date ;
    for(std::pair<QString,linkedList> Pair : user->list_of_tasks)
    {
        Task* task = Pair.second.head ;

        while(task != nullptr)
        {

            QStringList data = task->Due_Date.split(' ') ;
            if(task->notification && Date == data.at(0) && task->done == false)
            {
                qDebug() << data.at(0) ;

                show_notification("Tasks for today","You have to do " + task->Task_Name + " today.");
                break ;
            }
            task = task->next ;
        }
    }
}
void Professor_Panel::on_get_PDF_pushButton_clicked()
{
    getPDF(currentList);
}
void Professor_Panel::close_notif_Page()
{
    notification->close() ;
    this->show();
}

void Professor_Panel::on_get_stared_pushButton_clicked()
{
    Starred_Tasks = new starred_tasks(this) ;
    Starred_Tasks->get_list(user->list_of_tasks[currentList]);
    Starred_Tasks->load_starred_tasks();
    Starred_Tasks->show();
}
