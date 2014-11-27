#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T18:17:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DungeonV5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    combat_screen.cpp \
    lose_screen.cpp \
    item_screen.cpp \
    magic.cpp \
    win_screen.cpp

HEADERS  += mainwindow.h \
    declarations.h \
    combat_screen.h \
    hero.h \
    enemy.h \
    lose_screen.h \
    item_screen.h \
    magic.h \
    spider.h \
    win_screen.h

FORMS    += mainwindow.ui \
    combat_screen.ui \
    win_screen.ui \
    magic.ui \
    lose_screen.ui \
    item_screen.ui

RESOURCES += \
    Map.qrc
