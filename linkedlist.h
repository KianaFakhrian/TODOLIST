#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "task.h"

class linkedList
{
public:
    Task* head ;
    Task* tail ;
    QString name ;
    int size ;
public:
    linkedList()
    {
        init();
    }
    linkedList(linkedList const & ll)
    {
        head = nullptr ;
        tail = nullptr ;
        size = 0 ;
        Task* task = ll.head ;
        while(task != nullptr)
        {
            this->operator <<(*task);
            task = task->next ;
        }
    }
    void operator =(linkedList& LinkedList)
    {
        this->~linkedList() ;
        Task* task = LinkedList.head ;
        while(task != nullptr)
        {
            this->operator <<(*task);
            task = task->next ;
        }
    }

public:
    void operator << (Task task)
    {
        Task* New_Task = new Task() ;
        New_Task->set_task_info(task);

        if(head == nullptr)
        {
            New_Task->next = nullptr ;
            head = New_Task ;
            tail = New_Task ;
            size ++ ;
            return ;
        }

        New_Task->next = this->head ;
        head = New_Task ;
        size ++ ;

    }

    void init()
    {
        head = nullptr ;
        tail = nullptr ;
        size = 0 ;
    }
    void operator >> (Task task)
    {
        Task* New_Task = new Task() ;
        New_Task->set_task_info(task);
        if(head == nullptr)
        {
            this->operator <<(task);
            tail = New_Task ;
            tail->next = nullptr ;
            return ;
        }
        tail->next = New_Task ;
        tail = New_Task ;
        New_Task->next = nullptr ;
        size ++ ;

    }
    ~linkedList()
    {
        Task* task = head ;
        while(task != nullptr)
        {
            Task* tmp = task ;
            task = task->next ;
            delete tmp ;
        }
        head = nullptr ;
        size = 0 ;
        tail = nullptr ;
    }

    void set_Name(QString) ;
};

#endif // LINKEDLIST_H
