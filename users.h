#ifndef USERS_H
#define USERS_H
#include <QString>
#include <QStringList>
#include "linkedlist.h"
#include "task.h"

#endif // USERS_H
class Users{
public:
    QString username ;
    QString password ;
    linkedList Tasks ;
public:
    void loadDate(const QStringList& data )
    {
        if(data.size() >= 2)
        {
            username = data.at(0) ;
            password = data.at(1) ;
        }
    }
};
