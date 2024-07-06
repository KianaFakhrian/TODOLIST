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
#include <QHeaderView>
#include <QPixmap>
#include <QBrush>
#include <QVBoxLayout>
#include "QSidePanel/PanelRightSide.hpp"

// ---------------------------

#include <QTextEdit>
#include <QLabel>

// ---------------------------

#include "QSidePanel/math.hpp"

#include <QScroller>

#include "QSidePanel/side_panel_helpers.hpp"

Professor_Panel::Professor_Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Professor_Panel)
{
    ui->setupUi(this);

    ui->listWidget->hide();
    ui->list_color_comboBox->hide();
    ui->list_name_lineEdit->hide();
    ui->treeWidget->hide();
    ui->add_task_button->hide();
    ui->new_list_Button->hide();
    ui->dateTimeEdit->hide();
    ui->task_name_lineEdit->hide();
    ui->lineEdit_description->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->title->hide();

    QPixmap pixMap("/Users/HP/Documents/ToDoList/mentor.png") ;
    int width = 170 ;
    int height =170 ;
    QPixmap scaledPixmap = pixMap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(scaledPixmap);
    ui->label->setFixedSize(180,180) ;
    // Left panel with buttons list in it and line edits
       auto* panel_right = new PanelRightSide(this);
       {
           panel_right->setOpenEasingCurve (QEasingCurve::Type::OutExpo);
           panel_right->setCloseEasingCurve(QEasingCurve::Type::InExpo);
           panel_right->setPanelSize(350);
           panel_right->init();

           QVBoxLayout* lay = new QVBoxLayout;
           {
               QLabel* label = new QLabel("Left", this);
               label->setAlignment(Qt::AlignCenter);
               lay->addWidget(label);

               btn_list = new QPushButton( "Show list of Tasks", this);

               btn_PDF = new QPushButton( "Get PDF of tasks from list :", this);
               list_name_PDF = new QLineEdit() ;

               btn_starred = new QPushButton( "Get starred tasks from list :", this);
               list_name_star = new QLineEdit() ;

               btn_changeTheme = new QPushButton("Change Theme",this) ;

               btn_add_Task_or_list = new QPushButton("Add task or list",this) ;

               btn_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               btn_PDF->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               btn_starred->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               btn_changeTheme->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               btn_add_Task_or_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

               list_name_PDF->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
               list_name_star->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
               list_name_PDF->setPlaceholderText("Name of list") ;
               list_name_star->setPlaceholderText("Name of list") ;

               btn_list->setMinimumHeight(60);
               btn_starred->setMinimumHeight(60);
               btn_PDF->setMinimumHeight(60);
               btn_changeTheme->setMinimumHeight(60);
               btn_add_Task_or_list->setMinimumHeight(60);

               list_name_PDF->setMinimumHeight(10);
               list_name_star->setMinimumHeight(10);

               lay->addWidget(btn_list) ;
               lay->addWidget(btn_add_Task_or_list);
               lay->addWidget(btn_PDF);
               lay->addWidget(list_name_PDF);
               lay->addWidget(btn_starred);
               lay->addWidget(list_name_star);
               lay->addWidget(btn_changeTheme);

           }
           QWidget* proxy = new QWidget(this);
           proxy->setLayout(lay);

           panel_right->setWidgetResizable(true);
           panel_right->setWidget(proxy);

           // Extra behavior (for example) - scrolling by gestures. Notice, that
           // QScroller binded to `panel_left->viewport()`, not to `panel_left`
           {
               QScroller::grabGesture(panel_right->viewport(), QScroller::ScrollerGestureType::RightMouseButtonGesture);

               auto* scroller = QScroller::scroller(panel_right->viewport());
               {
                   // Improve buttons pressing. But still not good
                   QScrollerProperties props = scroller->scrollerProperties();
                   props.setScrollMetric(QScrollerProperties::ScrollMetric::MousePressEventDelay, 0);
                   scroller->setScrollerProperties(props);
               }
           }
       }


    // -------------------------------------------------------------------------

       connect(panel_right, &SidePanel::stateChanged, this, [this](SidePanelState state)
           {
               this->setWindowTitle( QString::fromUtf8( to_str(state) ) );
           });
    // -------------------------------------------------------------------------

    theme = new Theme(this) ;
    Themes[0] = "Red And White" ;
    Themes[1] = "Dark Theme" ;
    Themes[2] = "Whale" ;
    Themes[3] = "Plant" ;
    Themes[4] = "Simple" ;
    theme->get_themes(Themes);
    theme->load_pushButton_text();
    theme->get_target_window(this);

    connect(btn_list, SIGNAL(clicked()),this, SLOT(on_btn_list_clicked()));
    connect(btn_PDF, SIGNAL(clicked()),this, SLOT(on_btn_PDF_clicked()));
    connect(btn_starred, SIGNAL(clicked()),this, SLOT(on_btn_starred_clicked()));
    connect(btn_changeTheme, SIGNAL(clicked()),this, SLOT(on_btn_changeTheme_clicked()));
    connect(btn_add_Task_or_list, SIGNAL(clicked()),this, SLOT(on_btn_add_task_or_list()));



    ui->list_color_comboBox->addItem("Red");
    changeTheme("Light Theme") ;

    QStringList headers ;
    headers<< "description" << "Due Date" ;
    ui->treeWidget->setHeaderLabels(headers);
    ui->treeWidget->header()->setStyleSheet("QHeaderView::section { background-color: lightblue; }");
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
    item->setCheckState(0,Qt::Unchecked) ;
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
    int i = 0 ;
    for(std::pair<QString,linkedList> Pair : user->list_of_tasks)
    {
        Task* task = Pair.second.head ;

        while(task != nullptr)
        {

            QStringList data = task->Due_Date.split(' ') ;
            if(task->notification && Date == data.at(0) && task->done == false)
            {
                ui->title->setVisible(true);
                i ++ ;
                if(i == 1)
                {
                    ui->label_3->setVisible(true);
                    ui->label_3->setText(task->Task_Name);
                }
                else if(i == 2)
                {
                    ui->label_4->setVisible(true);
                    ui->label_4->setText(task->Task_Name);
                }
                else if(i == 3)
                {
                    ui->label_5->setVisible(true);
                    ui->label_5->setText(task->Task_Name);
                }
                else if(i == 4)
                {
                    ui->label_6->setVisible(true);
                    ui->label_6->setText(task->Task_Name);
                }
                else if(i == 5)
                {
                    ui->label_7->setVisible(true);
                    ui->label_7->setText(task->Task_Name);
                }
                show_notification("Tasks for today","You have to do " + task->Task_Name + " today.") ;
            }
            task = task->next ;
        }
    }
}

void Professor_Panel::set_username_label(QString Username)
{
    ui->username->setText( Username );
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

void Professor_Panel::on_btn_list_clicked()
{
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->username->hide();
    ui->label_7->hide();
    ui->title->hide();
    ui->listWidget->setVisible(true);
    load_list();
}

void Professor_Panel::on_btn_PDF_clicked()
{
    QString list_name = list_name_PDF->text() ;
    getPDF(list_name);
}

void Professor_Panel::on_btn_starred_clicked()
{
    QString list_name = list_name_star->text() ;
    Starred_Tasks = new starred_tasks(this) ;
    Starred_Tasks->get_list(user->list_of_tasks[list_name]);
    Starred_Tasks->load_starred_tasks();
    Starred_Tasks->show();
}

void Professor_Panel::on_btn_changeTheme_clicked()
{
        theme->show();
}

void Professor_Panel::on_btn_add_task_or_list()
{
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->username->hide();
    ui->label_7->hide();
    ui->title->hide();

    ui->add_task_button->setVisible(true);
    ui->new_list_Button->setVisible(true);
    ui->dateTimeEdit->setVisible(true);
    ui->list_name_lineEdit->setVisible(true);
    ui->task_name_lineEdit->setVisible(true);
    ui->treeWidget->setVisible(true);
    ui->lineEdit_description->setVisible(true);
    ui->list_color_comboBox->setVisible(true);
}

void Professor_Panel::on_get_stared_pushButton_clicked()
{
    Starred_Tasks = new starred_tasks(this) ;
    Starred_Tasks->get_list(user->list_of_tasks[currentList]);
    Starred_Tasks->load_starred_tasks();
    Starred_Tasks->show();
}
