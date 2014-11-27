#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextStream"
#include <iostream>
#include <sstream>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QKeyEvent>
#include <QDesktopWidget>
#include "declarations.h"
#include "combat_screen.h"
#include <vector>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setting Background image for TitleScreen Ui - Miguel
    QPixmap bg(":/Background.png");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);
    this->currentOption = 0;
    this->numOptions = 3;
    qApp->installEventFilter(this);

    this->inGame = false;

    mainChar = new Combat_Screen;
    mainChar->set_hero_health(100);
    mainChar->set_attacks(8,20);
    mainChar->set_defend(false);
    mainChar->set_lives(5);


    //Settting Pushbutton for NewGame Title - Miguel
    //QPixmap newGame(":/NewGame.png");
    //QIcon icon(newGame);
    //ui->pushButton->setIcon(icon);
    //ui->pushButton->setIconSize(newGame.size());

    //Setting Pusbutton 2 for QUIT Title    - Miguel
    //QPixmap quit(":/Quit.png");
    //QIcon icon2(quit);
    //ui->pushButton_2->setIcon(icon2);
    //ui->pushButton_2->setIconSize(quit.size());

    //Setting Pushbutton 3 for Options Title    - Miguel
    //QPixmap options(":/Options.png");
    //QIcon icon3(options);
    //ui->pushButton_3->setIcon(icon3);
    //ui->pushButton_3->setIconSize(quit.size());

    // from old MainWindow.cpp
    /*
        QPushButton *buttonUp = new QPushButton(this);
        QPushButton *buttonDown = new QPushButton;
        QPushButton *buttonLeft = new QPushButton;
        QPushButton *buttonRight = new QPushButton;*/

    this->gridLayout = new QGridLayout;
    this->gridLayout->setHorizontalSpacing(0);
    this->gridLayout->setVerticalSpacing(0);

    this->boardBoundX = 44;
    this->boardBoundY = 44;

    this->_curX = 0;
    this->_curY = this->boardBoundY;

    //Instantiating Qimages
    this->_path = QImage(":/PathRecent20x20.png");
    this->_wall = QImage(":/WallRecent20x20.png");
    this->_character = QImage(":/CharacterRecent20x20.png");
    this->_coffin = QImage(":/CoffinRecent20x20.png");              //Considering using this as a pickup item - Miguel

    this->_topLeft = QImage(":/TopLeft.png");                       //Upper Tile
    this->_topMiddle = QImage(":/TopMiddle.png");                   //Upper Tile
    this->_topRight = QImage(":/TopRight.png");                     //Upper Tile



    // this->_coffin = QImage(":/otherImage.png");                  //To be used for other images - Miguel
    // this->_coffin = QImage(":/otherImage.png");                  '' - Miguel
    // this->_coffin = QImage(":/otherImage.png");                  '' - Miguel

    for (int y = 0; y <= this->boardBoundY; y++) {
        for (int x = 0; x <= this->boardBoundX; x++) {
            QLabel *textBlock = new QLabel;
            if (this->boardMatrix[y][x] == 1)
                textBlock->setPixmap(QPixmap::fromImage(this->_wall));
            else if (this->boardMatrix[y][x] == 98) {
                this->_curX = x;
                this->_curY = y;
                textBlock->setPixmap(QPixmap::fromImage(this->_character));
            }
            else if (this->boardMatrix[y][x] == 2){
                textBlock->setPixmap(QPixmap::fromImage(this->_coffin));    //Currently used as a pickup() - Miguel

            }
            else if (this->boardMatrix[y][x] == 3){                          //Top left tile
                textBlock->setPixmap(QPixmap::fromImage(this->_topLeft));

            }
            else if (this->boardMatrix[y][x] == 4){                          //Top middle tile
                textBlock->setPixmap(QPixmap::fromImage(this->_topMiddle));

            }
            else if (this->boardMatrix[y][x] == 5){                          //Top right tile       1 through 5 will be unpassable
                textBlock->setPixmap(QPixmap::fromImage(this->_topRight));
            }
            else
                textBlock->setPixmap(QPixmap::fromImage(this->_path));
            gridLayout->addWidget(textBlock, y, x, 1, 1, Qt::AlignCenter);
        }
    }


    /*    buttonUp->setText("UP");
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

    */
    gameBoardWidget = new QWidget;
    gameBoardWidget->setLayout(gridLayout);
    gameBoardWidget->setWindowTitle("Dungeon");
    this->setFixedSize(800,500);
    this->centerWidget(true);

    /*QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - gameBoardWidget->width()) / 2;
    int y = (screenGeometry.height() - gameBoardWidget->height()) / 2;
    gameBoardWidget->move(x,y);*/


    // end old MainWindow.cpp
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::centerWidget(bool useSizeHint)
{
    if(this->centralWidget()->isFullScreen())
        return;

    QSize size;
    if(useSizeHint)
        size = this->centralWidget()->sizeHint();
    else
        size = this->centralWidget()->size();

    QDesktopWidget *d = QApplication::desktop();
    int ws = d->width();   // returns screen width
    int h = d->height();  // returns screen height
    int mw = size.width();
    int mh = size.height();
    int cw = (ws/2) - (mw/2);
    int ch = (h/2) - (mh/2);
    this->move(cw,ch);
}


int MainWindow::on_pushButton_clicked()
{
    return 0;
}

//Push Button to open the loading dialog
int MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
    return 0;
}

//Push button to open the options dialog
int MainWindow::on_pushButton_3_clicked()
{
    return 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (this->inGame) {
        if (event->key() == Qt::Key_Down)
            MainWindow::moveCharacter(MOVE_DOWN);
        else if (event->key() == Qt::Key_Left)
            MainWindow::moveCharacter(MOVE_LEFT);
        else if (event->key() == Qt::Key_Right)
            MainWindow::moveCharacter(MOVE_RIGHT);
        else if (event->key() == Qt::Key_Up)
            MainWindow::moveCharacter(MOVE_UP);

    } else {
        if (event->key() == Qt::Key_Down) {
            int oldOption = this->currentOption;
            this->currentOption++;
            if (this->currentOption == this->numOptions)
                this->currentOption = 0;
            this->updateMainMenu(oldOption, this->currentOption);
            //MainWindow::moveCharacter(MOVE_DOWN);
        }
        else if (event->key() == Qt::Key_Up) {
            int oldOption = this->currentOption;
            this->currentOption = this->currentOption - 1;
            if (this->currentOption == -1) {
                this->currentOption = this->numOptions-1;
            }
            this->updateMainMenu(oldOption, this->currentOption);
        } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return  ) {
            if (this->currentOption == 0) {
                this->inGame = true;
                if (this->centralWidget())
                    this->centralWidget()->setParent(0); // Preserve current central widget
                this->setCentralWidget(this->gameBoardWidget);
                this->setFixedSize(900,900);
                this->centerWidget(true);
                ui->pushButton->click();
            } else if (this->currentOption == 1) {
                ui->pushButton_3->click();
            } else if (this->currentOption == 2) {
                ui->pushButton_2->click();
            }
        }
    }
}

void MainWindow::updateMainMenu(int oldOption, int newOption) {

    QFont *newFont = new QFont("Terminal", 20, QFont::Bold);
    QFont *oldFont = new QFont("Terminal", 18, QFont::Normal);

    if (newOption == 0) {
        ui->pushButton->setText("[ NEW GAME ]");
        ui->pushButton->setFont(*newFont);
        //ui->pushButton->setStyleSheet("");
    } else if (newOption == 1) {
        ui->pushButton_3->setText("[  OPTION  ]");
        ui->pushButton_3->setFont(*newFont);
    } else if (newOption == 2) {
        ui->pushButton_2->setText("[   QUIT   ]");
        ui->pushButton_2->setFont(*newFont);
    }
    if (oldOption == 0) {
        ui->pushButton->setText("NEW GAME");
        ui->pushButton->setFont(*oldFont);
        //ui->pushButton->setStyleSheet("");
    } else if (oldOption == 1) {
        ui->pushButton_3->setText("OPTION");
        ui->pushButton_3->setFont(*oldFont);
    } else if (oldOption == 2) {
        ui->pushButton_2->setText("QUIT");
        ui->pushButton_2->setFont(*oldFont);
    }
}

bool MainWindow::eventFilter(QObject *obj,
                             QEvent *event)
{
    QKeyEvent *keyEvent = NULL;//event data, if this is a keystroke event
    bool result = false;//return true to consume the keystroke

    if (event->type() == QEvent::KeyPress)
    {
        //QTextStream(stdout) << "in eventFilter keyPress!";
        keyEvent = dynamic_cast<QKeyEvent*>(event);
        this->keyPressEvent(keyEvent);
        result = true;
    }//if type()

    else if (event->type() == QEvent::KeyRelease)
    {
        keyEvent = dynamic_cast<QKeyEvent*>(event);
        this->keyReleaseEvent(keyEvent);
        result = true;
    }//else if type()

    //### Standard event processing ###
    else
        result = QObject::eventFilter(obj, event);

    return result;
}//eventFilter

int MainWindow::checkMove(int direction) {
    int moveStatus;
    if (direction == MOVE_LEFT) {
        if (((_curX - 1) >= 0) && (this->boardMatrix[_curY][_curX-1] != 1)) {
            _curX--;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curX - 1 >= 0 ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_RIGHT) {
        if (((_curX + 1) <= this->boardBoundX) && (this->boardMatrix[_curY][_curX+1] != 1)) {
            _curX++;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curX + 1 <= boardBoundX ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_UP) {
        if (((_curY - 1) >= 0) && (this->boardMatrix[_curY-1][_curX] != 1)) {
            _curY--;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curY - 1 >= 0 ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_DOWN) {
        if (((_curY + 1) <= this->boardBoundY) && (this->boardMatrix[_curY+1][_curX] != 1)) {
            _curY++;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curY + 1 <= boardBoundY ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else
        moveStatus = MOVE_ERROR_UNKNOWN;

    if (moveStatus != MOVE_AUTHORIZED)
        return moveStatus;

    switch(this->boardMatrix[_curY][_curX]) {
    case CHARACTER_ENEMY: QTextStream(stdout) << "ENEMY";
                       break;
    case CHARACTER_BOSS: QTextStream(stdout) << "BOSS";
                       break;
    case CHARACTER_ITEM: QTextStream(stdout) << "ITEM";
                       break;
    default: return MOVE_AUTHORIZED;
    }
    return MOVE_AUTHORIZED;
}

void MainWindow::moveCharacter(int moveType) {
    int prevX = this->getX();
    int prevY = this->getY();

    int result = this->checkMove(moveType);
    if (result == MOVE_AUTHORIZED) {
        QLabel *oldLabel = (QLabel *)this->gridLayout->itemAtPosition(prevY, prevX)->widget();
        QLabel *newLabel = (QLabel *)this->gridLayout->itemAtPosition(this->getY(),this->getX())->widget();
        oldLabel->setPixmap(QPixmap::fromImage(this->_path));
        newLabel->setPixmap(QPixmap::fromImage(this->_character));
        if(this->boardMatrix[_curY][_curX]==CHARACTER_ENEMY){
            mainChar->show();
        }
    }
}



const int MainWindow::boardMatrix[45][45] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,CHARACTER_BOSS,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,2,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,2,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,2,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,2,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,CHARACTER_ENEMY,0,2,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,CHARACTER_ENEMY,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,CHARACTER_ENEMY,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,CHARACTER_SPAWN,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                             {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};


