#ifndef PROFESSOR_PANEL_H
#define PROFESSOR_PANEL_H

#include <QMainWindow>
#include "user.h"
#include "linkedlist.h"
#include "notification.h"
#include "starred_tasks.h"
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QSystemTrayIcon>
#include <QApplication>
#include "file_functions.h"
#include <QMap>
namespace Ui {
class Professor_Panel;
}

class Professor_Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Professor_Panel(QWidget *parent = 0);
    virtual ~Professor_Panel();
public:
    void get_Users(QList<User>* users_List) ;

    void add_Task() ;

    void add_list() ;

    void set_User(User*) ;

    void load_list() ;

    void load_tasks() ;

    void search_user() ;

    void add_Child(QTreeWidgetItem* parent,QString description,QString due_date) ;

    void loadTheme(const QString &) ;

    void getPDF(const QString &) ;

    void showing_notif() ;

    void show_notification(const QString &title,const QString &message) ;

    void change_List_Color(QListWidgetItem*,const QColor&) ;

public slots:
    void on_add_task_button_clicked();

    void on_new_list_Button_clicked();

    void switch_list(QListWidgetItem* item) ;

    void update_tasks(QTreeWidgetItem*) ;

    void star_task(QTreeWidgetItem*) ;

    void changeTheme(const QString &) ;

    void on_get_PDF_pushButton_clicked();

    void on_get_stared_pushButton_clicked();

    void close_notif_Page() ;

protected:
    Ui::Professor_Panel *ui;
    QString task_name ;
    QString due_date ;
    User* user ;
    QList<User>* users ;
    Notification* notification ;
    starred_tasks* Starred_Tasks ;
    QString currentList;
    QMenu *taskListMenu;
    QSystemTrayIcon *trayIcon;
};

#endif // PROFESSOR_PANEL_H
