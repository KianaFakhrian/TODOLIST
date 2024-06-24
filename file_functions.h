#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H
#include "task.h"
#include "linkedlist.h"
#include "users.h"
#include <QList>

class File_Functions
{
public:
    File_Functions();
public:
    void read_Users_From_File(const QString& filePath ,QList<Users>& users)
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

            Users tmp_user ;
            tmp_user.loadData(data) ;
            users.pushFront(tmp_user);
        }
        file.close();
    }

    void write_Tasks_To_File(const QString&filePath , linkedList tasks)
    {
        QFile file(filePath);

        if (!file.open(QFile::Append | QFile::Text)) {
            qWarning() << "Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file) ;

            out << tasks.Task_Name << " " << tasks.Due_Date << " "
                << tasks.Explanation << "/n" ;

        file.close();
    }

};
#endif // FILE_FUNCTIONS_H
