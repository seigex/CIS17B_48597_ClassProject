#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "titlescreen.h"
#include <iostream>
#include <sstream>
#include <QWidget>
#include <QSignalMapper>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *buttonUp = new QPushButton(this);
    QPushButton *buttonDown = new QPushButton;
    QPushButton *buttonLeft = new QPushButton;
    QPushButton *buttonRight = new QPushButton;

    this->gridLayout = new QGridLayout;

    this->boardBoundX = 11;
    this->boardBoundY = 11;

    this->_curX = 0;
    this->_curY = this->boardBoundY;

    for (int y = 0; y <= this->boardBoundY; y++) {
        for (int x = 0; x <= this->boardBoundX; x++) {
            QLabel *textBlock = new QLabel;

            if (x == 0 && y == this->boardBoundY)
                textBlock->setText("<span style='color:red'>X</span>");
            else {
                textBlock->setText(QString("<span style='color:black'>%1</span>").arg(this->boardMatrix[y][x]));
            }
            gridLayout->addWidget(textBlock, y, x, 1, 1, Qt::AlignCenter);
        }
    }


    buttonUp->setText("UP");
    buttonDown->setText("DOWN");
    buttonLeft->setText("LEFT");
    buttonRight->setText("RIGHT");

    QSignalMapper *signalMapper = new QSignalMapper(this);
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(moveCharacter(int)));
    QObject::connect(buttonUp, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(buttonDown, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(buttonLeft, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(buttonRight, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(buttonUp, MOVE_UP);
    signalMapper->setMapping(buttonDown, MOVE_DOWN);
    signalMapper->setMapping(buttonLeft, MOVE_LEFT);
    signalMapper->setMapping(buttonRight, MOVE_RIGHT);

    gridLayout->addWidget(buttonUp, this->boardBoundY + 1, 0, 1, 3, Qt::AlignCenter);
    gridLayout->addWidget(buttonDown, this->boardBoundY + 1, 3, 1, 3, Qt::AlignCenter);
    gridLayout->addWidget(buttonLeft, this->boardBoundY + 1, 6, 1, 3, Qt::AlignCenter);
    gridLayout->addWidget(buttonRight, this->boardBoundY + 1, 9, 1, 3, Qt::AlignCenter);

    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(gridLayout);
    mainWidget->setWindowTitle("Test");

    if (this->centralWidget())
        this->centralWidget()->setParent(0); // Preserve current central widget
    this->setCentralWidget(mainWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::checkMove(int direction) {
    if (direction == MOVE_LEFT) {
        if (((_curX - 1) >= 0) && (this->boardMatrix[_curY][_curX-1] != 1)) {
            _curX--;
            return MOVE_AUTHORIZED;
        } else
            return _curX - 1 >= 0 ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_RIGHT) {
        if (((_curX + 1) <= this->boardBoundX) && (this->boardMatrix[_curY][_curX+1] != 1)) {
            _curX++;
            return MOVE_AUTHORIZED;
        } else
            return _curX + 1 <= boardBoundX ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_UP) {
        if (((_curY - 1) >= 0) && (this->boardMatrix[_curY-1][_curX] != 1)) {
            _curY--;
            return MOVE_AUTHORIZED;
        } else
            return _curY - 1 >= 0 ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_DOWN) {
        if (((_curY + 1) <= this->boardBoundY) && (this->boardMatrix[_curY+1][_curX] != 1)) {
            _curY++;
            return MOVE_AUTHORIZED;
        } else
            return _curY + 1 <= boardBoundY ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else
        return MOVE_ERROR_UNKNOWN;
}

 void MainWindow::moveCharacter(int moveType) {
    int prevX = this->getX();
    int prevY = this->getY();

    int result = this->checkMove(moveType);
             if (result == MOVE_AUTHORIZED) {
                 QLabel *oldLabel = (QLabel *)this->gridLayout->itemAtPosition(prevY, prevX)->widget();
                 QLabel *newLabel = (QLabel *)this->gridLayout->itemAtPosition(this->getY(),this->getX())->widget();
                 oldLabel->setText(QString("<span style='color:black'>%1</span>").arg(this->boardMatrix[prevY][prevX]));
                 newLabel->setText("<span style='color:red'>X</span>");
             }
}

const int MainWindow::boardMatrix[12][12] = {{0,0,0,0,0,0,1,1,0,0,0,0},
                                             {0,0,0,0,0,0,1,1,0,0,0,0},
                                             {0,0,0,0,0,0,1,1,0,0,0,0},
                                             {0,0,0,0,0,0,1,1,0,0,0,0},
                                             {0,0,0,0,0,0,1,1,0,0,0,0},
                                             {0,0,0,0,0,0,0,1,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,1,0,0,0,0,0},
                                             {0,0,0,0,0,1,1,0,0,0,0,0},
                                             {0,0,0,0,0,1,1,0,0,0,0,0},
                                             {0,0,0,1,1,1,1,1,0,0,0,0},
                                             {0,0,1,1,1,1,1,1,1,0,0,0}};

