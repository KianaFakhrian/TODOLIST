#ifndef STUDENT_PANEL_H
#define STUDENT_PANEL_H

#include <QMainWindow>

namespace Ui {
class Student_Panel;
}

class Student_Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Panel(QWidget *parent = 0);
    ~Student_Panel();

private:
    Ui::Student_Panel *ui;
};

#endif // STUDENT_PANEL_H
