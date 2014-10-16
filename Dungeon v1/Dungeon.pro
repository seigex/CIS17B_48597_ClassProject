#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T17:49:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dungeon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    titlescreen.cpp \
    help.cpp

HEADERS  += mainwindow.h \
    declarations.h \
    titlescreen.h \
    help.h

FORMS    += mainwindow.ui \
    titlescreen.ui
