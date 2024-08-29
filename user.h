#ifndef USER_H
#define USER_H
#include "linkedlist.h"
#include <map>

class User
{

public:
    QString username ;
    QString password ;
    std::map<QString,linkedList> list_of_tasks ;
public:
    void loadData(const QStringList& data )
    {
        if(data.size() >= 2)
        {
            username = data.at(0) ;
            password = data.at(1) ;
        }
    }
};

#endif // USER_H
