#-------------------------------------------------
#
# Project created by QtCreator 2024-06-23T16:54:39
#
#-------------------------------------------------

QT       += core gui
QT += printsupport
include(/Users/HP/Documents/ToDoList/QSidePanel-Sidebar-master/QSidePanel/q_side_panel.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToDoList
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        mainwindow.cpp \
    linkedlist.cpp \
    student_panel.cpp \
    professor_panel.cpp \
    sign_in.cpp \
    notification.cpp \
    starred_tasks.cpp \
    theme.cpp

HEADERS  += mainwindow.h \
    linkedlist.h \
    task.h \
    file_functions.h \
    user.h \
    student_panel.h \
    professor_panel.h \
    sign_in.h \
    notification.h \
    starred_tasks.h \
    theme.h

FORMS    += mainwindow.ui \
    student_panel.ui \
    professor_panel.ui \
    sign_in.ui \
    notification.ui \
    starred_tasks.ui \
    theme.ui

RESOURCES += \
    theme.qrc

DISTFILES += \
    darkTheme.qss \
    QSidePanel-Sidebar-master/QSidePanel/q_side_panel.pri \
    QSidePanel-Sidebar-master/images/side_panel.gif \
    QSidePanel-Sidebar-master/LICENSE \
    QSidePanel-Sidebar-master/README.md

SUBDIRS += \
    QSidePanel-Sidebar-master/q_side_panel_proj.pro
