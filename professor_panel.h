#ifndef PROFESSOR_PANEL_H
#define PROFESSOR_PANEL_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class Professor_Panel;
}

class Professor_Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Professor_Panel(QWidget *parent = 0);
    ~Professor_Panel();
public:
    void get_Users(QList<User>* users_List) ;

private:
    Ui::Professor_Panel *ui;
    QList<User>* users ;
};

#endif // PROFESSOR_PANEL_H
