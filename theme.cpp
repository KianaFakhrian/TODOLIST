#include "theme.h"
#include "ui_theme.h"

Theme::Theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theme)
{
    ui->setupUi(this);
}

Theme::~Theme()
{
    delete ui;
}
