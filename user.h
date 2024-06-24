#ifndef USER_H
#define USER_H
#include "linkedlist.h"

class User
{

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

#endif // USER_H
