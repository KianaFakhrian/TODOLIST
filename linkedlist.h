#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "task.h"

class linkedList
{
public:
    Task* head ;
    QString name ;
public:
    linkedList()
    {
        init();
    }

public:
    void operator << (Task task)
    {
        Task* New_Task = new Task() ;
        New_Task->set_task_info(task);

        New_Task->next = this->head ;
        head = New_Task ;
    }

    void init()
    {
        head = nullptr ;
    }

    void set_Name(QString) ;
};

#endif // LINKEDLIST_H
