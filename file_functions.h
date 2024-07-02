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

            out << users.username << "," << users.password << "\n" ;

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
            QStringList data = line.split(',');

            User tmp_user ;
            tmp_user.loadData(data);
            users.append(tmp_user);
        }
        file.close();
    }

    static void write_Tasks_To_File(const QString&filePath , Task tasks,QString username,QString list_name)
    {
        QFile file(filePath);
        if (!file.open(QFile::Append | QFile::Text)) {
            qWarning() << "Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file) ;

            out <<username<<","<< list_name << "," <<tasks.Task_Name << "," << tasks.Due_Date << ","
                << tasks.Explanation << ","<< QString::number(tasks.Star) <<"," << QString::number(tasks.done) << "\n" ;

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
            QStringList data = line.split(',') ;

            if(data.size() >= 7)
            {
                QString username = data.at(0) ;
                QString list_name = data.at(1) ;
                Task task ;
                task.loadData(data.mid(2));

                for(User& Users : users)
                {
                    if(Users.username == username)
                    {
                        Users.list_of_tasks[list_name] << task ;
                    }
                }
            }
        }
        file.close();
    }
    static void updateDoneTask(const QString& filePath,QList<User> users,QString list_name,const QString task_name,bool done,QString username)
    {
        QString updated_line ;
        bool userFound = false ;
        for( User users_list: users)
        {
            if(users_list.username == username)
            {
                Task* task = users_list.list_of_tasks[list_name].head ;
                while(task != nullptr)
                {
                    if(task->Task_Name == task_name)
                        break ;
                    task = task->next ;
                }
                updated_line = users_list.username + "," + list_name + "," + task_name + "," +
                        task->Due_Date + "," + task->Explanation + "," +
                        QString::number(task->Star) + "," + QString::number(done);
                userFound = true ;
                break ;
            }
            if(userFound)
                break ;

        }

            QFile originalFile(filePath);
            if (!originalFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Failed to open original file for reading:" << originalFile.errorString();
                return;
            }
            QString tempFilePath = filePath + ".tmp";
            QFile tempFile(tempFilePath);
            if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qWarning() << "Failed to create temporary file:" << tempFile.errorString();
                originalFile.close();
                return;
            }

            QTextStream out(&tempFile);

            QTextStream in(&originalFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList data = line.split(',');

                if (data.size() >= 7 && data[0] == username &&
                        data[1] == list_name &&data[2] == task_name) {
                    out << updated_line << '\n';
                } else {
                    out << line << '\n';
                }
            }

            originalFile.close();
            tempFile.close();

            if (!QFile::remove(filePath)) {
                qWarning() << "Failed to remove original file:" << filePath;
            } else {
                if (!QFile::rename(tempFilePath, filePath)) {
                    qWarning() << "Failed to rename temporary file to original file:" << tempFilePath;
                } else {
                    qDebug() << "File updated successfully.";
                }
            }
        }

    static void updateStaredTask(const QString& filePath,QList<User> users,QString list_name,const QString task_name,bool star,QString username)
    {


        QString updated_line ;
        bool userFound = false ;
        for( User users_list: users)
        {
            if(users_list.username == username)
            {
                Task* task = users_list.list_of_tasks[list_name].head ;
                while(task != nullptr)
                {
                    if(task->Task_Name == task_name)
                        break ;
                    task = task->next ;
                }
                updated_line = users_list.username + "," + list_name + "," + task_name + "," +
                        task->Due_Date + "," + task->Explanation + "," +
                        QString::number(star) + "," + QString::number(task->done);
                userFound = true ;
                break ;
            }
            if(userFound)
                break ;

        }

            QFile originalFile(filePath);
            if (!originalFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Failed to open original file for reading:" << originalFile.errorString();
                return;
            }
            QString tempFilePath = filePath + ".tmp";
            QFile tempFile(tempFilePath);
            if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qWarning() << "Failed to create temporary file:" << tempFile.errorString();
                originalFile.close();
                return;
            }

            QTextStream out(&tempFile);

            QTextStream in(&originalFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList data = line.split(',');

                if (data.size() >= 7 && data[0] == username &&
                        data[1] == list_name &&data[2] == task_name) {
                    out << updated_line << '\n';
                } else {
                    out << line << '\n';
                }
            }

            originalFile.close();
            tempFile.close();

            if (!QFile::remove(filePath)) {
                qWarning() << "Failed to remove original file:" << filePath;
            } else {
                if (!QFile::rename(tempFilePath, filePath)) {
                    qWarning() << "Failed to rename temporary file to original file:" << tempFilePath;
                } else {
                    qDebug() << "File updated successfully.";
                }
            }
        }

};
#endif // FILE_FUNCTIONS_H
