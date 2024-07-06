#ifndef PROFESSOR_PANEL_H
#define PROFESSOR_PANEL_H

#include <QMainWindow>
#include "user.h"
#include "linkedlist.h"
#include "notification.h"
#include "starred_tasks.h"
#include "theme.h"
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

    void set_User(User*) ;

    void add_Task() ;

    void add_list() ;

    void load_list() ;

    void load_tasks() ;

    void add_Child(QTreeWidgetItem* parent,QString description,QString due_date) ;

    void loadTheme(const QString &) ;

    void show_notification(const QString &title,const QString &message) ;

    void change_List_Color(QListWidgetItem*,const QColor&) ;

    void showing_notif() ;

    void set_username_label(QString Username) ;

private:
    void getPDF(const QString &) ;

private slots:
    void on_add_task_button_clicked();

    void on_new_list_Button_clicked();

    void switch_list(QListWidgetItem* item) ;

    void update_tasks(QTreeWidgetItem*) ;

    void star_task(QTreeWidgetItem*) ;

    void changeTheme(const QString &) ;

    void on_get_PDF_pushButton_clicked();

    void on_get_stared_pushButton_clicked();

    void close_notif_Page() ;

    void on_btn_list_clicked() ;

    void on_btn_PDF_clicked() ;

    void on_btn_starred_clicked() ;

    void on_btn_changeTheme_clicked() ;

    void on_btn_add_task_or_list() ;


protected:
    Ui::Professor_Panel *ui;
    QString task_name ;
    QString due_date ;
    QList<User>* users ;
    Notification* notification ;
    starred_tasks* Starred_Tasks ;
    QString currentList;
    QSystemTrayIcon *trayIcon;
    QLineEdit* list_name_star ;
    QLineEdit* list_name_PDF ;
    QPushButton* btn_list  ;
    QPushButton* btn_PDF ;
    QPushButton* btn_starred ;
    QPushButton* btn_changeTheme ;
    QPushButton* btn_add_Task_or_list ;
    Theme* theme ;
    QString Themes[5] ;
private:
    User* user ;
};

#endif // PROFESSOR_PANEL_H
