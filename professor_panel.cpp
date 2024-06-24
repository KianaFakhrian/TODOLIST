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
