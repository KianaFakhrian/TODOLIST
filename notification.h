#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QDialog>
#include "user.h"
#include "task.h"

namespace Ui {
class Notification;
}

class Notification : public QDialog
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = 0);
    ~Notification();
public:
    void get_user(User*) ;
    void get_list_name(QString) ;
    void get_task_name(QString) ;
    void get_users(QList<User>*) ;
    void update_file() ;
private slots:
    void on_Yes_clicked();

    void on_No_clicked();

    void search_Task() ;
signals :
    void exit() ;
private:
    Ui::Notification *ui;
    User* user ;
    QList<User>* users ;
    Task* task ;
    QString list_name ;
    QString task_name ;
};

#endif // NOTIFICATION_H
