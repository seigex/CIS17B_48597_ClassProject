#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <sstream>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include "declarations.h"
#include <vector>
#include "ui_titlescreen.h"
namespace Ui {
class MainWindow;
class TitleScreen;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    int boardBoundX;
    int boardBoundY;
    static const int boardMatrix[12][12];
    int checkMove(int direction);
    int getX() {return this->_curX;}
    int getY() {return this->_curY;}

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int _curX;
    int _curY;
    QGridLayout *gridLayout;

private slots:
    void moveCharacter(int moveType);


};

#endif // MAINWINDOW_H
