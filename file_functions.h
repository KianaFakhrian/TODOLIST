#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H
#include "task.h"
#include "linkedlist.h"
#include "user.h"
#include <QList>
#include <QDebug>

class File_Functions
{
public:
    File_Functions();
public:
    static void write_Users_To_File(const QString& filePath ,User& users)
    {
        QFile file(filePath);

        if (!file.open(QFile::Append | QFile::Text)) {
            qWarning() << "Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file) ;

            out << users.username << " " << users.password << "\n" ;

        file.close();
    }

    static void read_Users_From_File(const QString& filePath ,QList<User>& users)
    {
        QFile file(filePath) ;
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            qWarning() << "file couldn't be open" << file.errorString() ;
            return ;
        }
        QTextStream in(&file) ;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList data = line.split(' ');

            User tmp_user ;
            tmp_user.loadDate(data);
            users.append(tmp_user);
        }
        file.close();
    }

    static void write_Tasks_To_File(const QString&filePath , Task tasks,QString username)
    {
        QFile file(filePath);

        if (!file.open(QFile::Append | QFile::Text)) {
            qWarning() << "Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file) ;

            out <<username << " " <<tasks.Task_Name << " " << tasks.Due_Date << " "
                << tasks.Explanation << " "<< tasks.Star <<"/n" ;

        file.close();
    }
    static void read_Tasks_From_File(const QString& filepath , QList<User>& users)
    {
        QFile file(filepath) ;

        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            qWarning() << "file couldn't be open" << file.errorString() ;
            return ;
        }
        QTextStream in(&file) ;
        while(!in.atEnd())
        {
            QString line = in.readLine() ;
            QStringList data = line.split(' ') ;

            if(data.size() >= 5)
            {
                QString username = data.at(0) ;
                Task task ;
                task.loadData(data.mid(1));

                for(User& Users : users)
                {
                    if(Users.username == username)
                        Users.Tasks.pushFront(task);
                }
            }
        }
        file.close();
    }
};
#endif // FILE_FUNCTIONS_H
