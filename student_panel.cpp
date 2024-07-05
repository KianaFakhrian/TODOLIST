#include "student_panel.h"
#include "ui_student_panel.h"

Student_Panel::Student_Panel(QWidget *parent) :
    Professor_Panel(parent),
    ui(new Ui::Student_Panel)
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

Student_Panel::~Student_Panel()
{
    delete ui;
}

void Student_Panel::get_Users(QList<User> *users_List)
{
    users = users_List ;
}
