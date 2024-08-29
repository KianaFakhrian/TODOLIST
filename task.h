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
    bool Star;
    bool done;
    bool notification ;
    Task* next ;
public:
    void set_task_info(Task New_Task)
    {
        Task_Name = New_Task.Task_Name ;
        Due_Date = New_Task.Due_Date ;
        Explanation = New_Task.Explanation ;
        Star = New_Task.Star ;
        done = New_Task.done ;
        notification = New_Task.notification ;
    }
    void loadData(const QStringList& data)
    {
        if(data.size() >= 6)
        {
            Task_Name = data.at(0) ;
            Due_Date = data.at(1) ;
            Explanation = data.at(2) ;
            if(data.at(3) == "1")
                Star = true ;
            else
                Star = false ;
            if(data.at(4) == "1")
                done = true ;
            else
                done = false ;
            if(data.at(5) == "1")
                notification = true ;
            else
                notification = false ;

        }
    }
};

#endif // TASK_H
