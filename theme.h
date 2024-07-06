#ifndef THEME_H
#define THEME_H

#include <QDialog>

namespace Ui {
class Theme;
}

class Theme : public QDialog
{
    Q_OBJECT

public:
    explicit Theme(QWidget *parent = 0);
    ~Theme();
public:
    void load_theme(const QString &) ;

    void change_theme(const QString&) ;

    void load_pushButton_text() ;

    void get_themes(QString Theme[]) ;

    QString set_theme_chosen(QString) ;

    void get_target_window(QWidget *window) ;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_close_pushButton_clicked();

private:
    Ui::Theme *ui;
    QString themes[5] ;
    QWidget *target_window;
};

#endif // THEME_H
