#ifndef STARRED_TASKS_H
#define STARRED_TASKS_H

#include <QMainWindow>
#include "linkedlist.h"

namespace Ui {
class starred_tasks;
}

class starred_tasks : public QMainWindow
{
    Q_OBJECT

public:
    explicit starred_tasks(QWidget *parent = 0);
    ~starred_tasks();
public:
    void load_starred_tasks() ;
    void get_list(linkedList&) ;
private slots:
    void on_close_pushButton_clicked();

private:
    Ui::starred_tasks *ui;
    linkedList task_lists ;
};

#endif // STARRED_TASKS_H
