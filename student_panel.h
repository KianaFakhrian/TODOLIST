#ifndef STUDENT_PANEL_H
#define STUDENT_PANEL_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class Student_Panel;
}

class Student_Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Panel(QWidget *parent = 0);
    ~Student_Panel();
public:
    void get_Users(QList<User>* users) ;

private:
    Ui::Student_Panel *ui;
    QList<User>* users ;
};

#endif // STUDENT_PANEL_H
