#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <sstream>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
//#include "declarations.h"
#include <vector>
#include "combat_screen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int boardBoundX;
    int boardBoundY;
    static const int boardMatrix[45][45];
    int checkMove(int direction);
    int getX() {return this->_curX;}
    int getY() {return this->_curY;}
    void centerWidget(bool useSizeHint);

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
    int currentOption;
    int numOptions;
    bool eventFilter(QObject *obj, QEvent *event);
    void updateMainMenu(int oldOption, int newOption);
    QPushButton mainButtons[3];
    QWidget *gameBoardWidget;

    bool inGame;
    int _curX;
    int _curY;
    QGridLayout *gridLayout;
    QImage _path;
    QImage _wall;
    QImage _character;
    QImage _coffin;         //Cosmetic wall To be represented by #2 in array
    QImage _topLeft;
    QImage _topMiddle;
    QImage _topRight;
    Combat_Screen *mainChar;

private slots:
    int on_pushButton_clicked();
    int on_pushButton_2_clicked();
    int on_pushButton_3_clicked();
    void moveCharacter(int moveType);
};
#endif // MAINWINDOW_H
