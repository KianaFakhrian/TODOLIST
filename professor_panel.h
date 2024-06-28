#ifndef PROFESSOR_PANEL_H
#define PROFESSOR_PANEL_H

#include <QMainWindow>
#include "user.h"
#include "linkedlist.h"
#include <QListWidgetItem>
#include "file_functions.h"
#include <QMap>
#include <QMenu>
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
//    void delete_tasks(QListWidgetItem*) ;
    void set_User(User*) ;
    void load_list() ;
    void load_tasks() ;
    void search_user() ;



private slots:
    void on_add_task_button_clicked();

    void on_new_list_Button_clicked();

    void switch_list(QListWidgetItem* item) ;

//    void on_listWidget_itemClicked(QListWidgetItem *item);

    void update_tasks(QListWidgetItem*) ;

    void star_task(QListWidgetItem*) ;

private:
    Ui::Professor_Panel *ui;
    QString task_name ;
    QString due_date ;
    User* user ;
    QList<User>* users ;
    QString currentList;
    QMenu *taskListMenu;
};

#endif // PROFESSOR_PANEL_H
