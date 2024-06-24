#include "student_panel.h"
#include "ui_student_panel.h"

Student_Panel::Student_Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Student_Panel)
{
    ui->setupUi(this);
}

Student_Panel::~Student_Panel()
{
    delete ui;
}

void Student_Panel::get_Users(QList<User> *users_List)
{
    users = users_List ;
}
