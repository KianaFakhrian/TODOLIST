#include "professor_panel.h"
#include "ui_professor_panel.h"

Professor_Panel::Professor_Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Professor_Panel)
{
    ui->setupUi(this);
}

Professor_Panel::~Professor_Panel()
{
    delete ui;
}

void Professor_Panel::get_Users(QList<User> *Users_List)
{
    users = Users_List ;
}
