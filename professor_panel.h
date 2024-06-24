#ifndef PROFESSOR_PANEL_H
#define PROFESSOR_PANEL_H

#include <QMainWindow>

namespace Ui {
class Professor_Panel;
}

class Professor_Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Professor_Panel(QWidget *parent = 0);
    ~Professor_Panel();

private:
    Ui::Professor_Panel *ui;
};

#endif // PROFESSOR_PANEL_H
