#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "file_functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readUsers();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readUsers()
{
    File_Functions::read_Users_From_File("Users.txt",users_list) ;
}
