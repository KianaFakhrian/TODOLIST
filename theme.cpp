#include "theme.h"
#include "ui_theme.h"
#include <QFile>
#include <QTextStream>
Theme::Theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theme)
{
    ui->setupUi(this);

}

Theme::~Theme()
{
    delete ui;
}

void Theme::load_pushButton_text()
{
    ui->pushButton->setText(themes[0]);
    ui->pushButton_2->setText(themes[1]);
    ui->pushButton_3->setText(themes[2]);
    ui->pushButton_4->setText(themes[3]);
    ui->pushButton_5->setText(themes[4]);
}
void Theme::load_theme(const QString &themeFile)
{
    QFile file(themeFile);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        target_window->setStyleSheet(styleSheet);
        file.close();
    }
}

void Theme::change_theme(const QString& theme)
{
    if(theme == "Dark Theme")
        load_theme(":/new/prefix1/darkTheme.qss");
    else if(theme == "Light Theme")
        load_theme(":/new/prefix1/Light Theme.qss");
    else if(theme == "chocolate")
        load_theme(":/new/prefix1/chocolate.qss");
    else if(theme == "Black and green")
        load_theme(":/new/prefix1/Green and black.qss");
    else if(theme == "Rose")
            load_theme(":/new/prefix1/Rose.qss");
    else if(theme == "Red And White")
        load_theme(":/new/prefix1/Red and White.qss");
    else if(theme == "Whale")
        load_theme(":/new/prefix1/whale.qss");

}
QString Theme::set_theme_chosen(QString Theme)
{
    return Theme ;
}

void Theme::get_target_window(QWidget *window)
{
    target_window = window ;
}

void Theme::get_themes(QString Theme[5])
{
    for(int i = 0 ; i < 5 ;i ++)
    {
        themes[i] = Theme[i] ;
    }
}

void Theme::on_pushButton_clicked()
{
    change_theme( ui->pushButton->text()) ;
}
void Theme::on_pushButton_2_clicked()
{
    change_theme( ui->pushButton_2->text()) ;
}

void Theme::on_pushButton_3_clicked()
{
    change_theme( ui->pushButton_3->text()) ;
}

void Theme::on_pushButton_4_clicked()
{
    change_theme( ui->pushButton_4->text()) ;
}

void Theme::on_pushButton_5_clicked()
{
    change_theme( ui->pushButton_5->text()) ;
}

void Theme::on_close_pushButton_clicked()
{
    this->hide();
}
