#ifndef STUDENT_PANEL_H
#define STUDENT_PANEL_H

#include <QMainWindow>
#include "user.h"
#include "professor_panel.h"
#include "theme.h"

namespace Ui {
class Student_Panel;
}

class Student_Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Panel(QWidget *parent = 0);
    ~Student_Panel();
private slots:

    void switch_list(QListWidgetItem* item) ;

    void update_tasks(QTreeWidgetItem*) ;

    void star_task(QTreeWidgetItem*) ;

    void close_notif_Page() ;

    void on_add_new_list_pushButton_clicked();

    void on_add_new_task_pushButton_clicked();

    void on_get_starred_pushButton_clicked();

    void on_get_PDF_pushButton_clicked();

    void on_btn_list_clicked() ;

    void on_btn_PDF_clicked() ;

    void on_btn_starred_clicked() ;

    void on_btn_changeTheme_clicked() ;

    void on_btn_add_task_or_list() ;

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

    void get_PDF(const QString&) ;

    void set_username_label(QString Username) ;

private:
    Ui::Student_Panel *ui;
    User* user ;
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
public:
    QString Theme_Chosen ;
};

#endif // STUDENT_PANEL_H
