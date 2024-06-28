#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QStringList>

class Task
{
public:
    QString Task_Name ;
    QString Due_Date ;
    QString Explanation = " " ;
    bool Star ;
    bool done;
    Task* next ;
public:
    void set_task_info(Task New_Task)
    {
        Task_Name = New_Task.Task_Name ;
        Due_Date = New_Task.Due_Date ;
        Explanation = New_Task.Explanation ;
        Star = New_Task.Star ;
    }
    void loadData(const QStringList& data)
    {
        if(data.size() >= 5)
        {
            Task_Name = data.at(0) ;
            Due_Date = data.at(1) ;
            Explanation = data.at(2) ;
            Star = (data.at(3) == "0");
            done = (data.at(4) == "0") ;
        }
    }
};

#endif // TASK_H
