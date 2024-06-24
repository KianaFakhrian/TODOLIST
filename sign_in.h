#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMainWindow>

namespace Ui {
class Sign_In;
}

class Sign_In : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sign_In(QWidget *parent = 0);
    ~Sign_In();

private:
    Ui::Sign_In *ui;
};

#endif // SIGN_IN_H
