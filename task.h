#ifndef TASK_H
#define TASK_H
#include <QString>

class Task
{
public:
    QString Task_Name ;
    QString Due_Date ;
    QString Explanation ;
    bool Star;
    Task* next ;
public:
    Task();
    void set_task_info(Task New_Task)
    {

        Task_Name = New_Task.Task_Name ;
        Due_Date = New_Task.Due_Date ;
        Explanation = New_Task.Explanation ;
        Star = New_Task.Star ;
    }

};

#endif // TASK_H
