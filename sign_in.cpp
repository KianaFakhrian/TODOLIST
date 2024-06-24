#include "sign_in.h"
#include "ui_sign_in.h"

Sign_In::Sign_In(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sign_In)
{
    ui->setupUi(this);
}

Sign_In::~Sign_In()
{
    delete ui;
}
