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
#include <QDialog>
#include <QDesktopWidget>
#include "declarations.h"
#include "combat_screen.h"
#include "help_screen.h"
#include <vector>
#include <QDir>
#include <QDebug>
#include <QtSql>
#include <QSqlQueryModel>
#include <QString>
#include "savedgame.h"
#include <QTextStream>
#include "loadfiles.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_curX = 2;
    this->_curY = 42;
    this->_curHealth = 100;

    QDir qDir;

    savedGames.Load(QString(qDir.absolutePath()+"/CONFIG/"), QString("savedgames.txt"));

    if (savedGames.GetIsLoaded()) {
        if (savedGames.GetSavedGameCount() > 0) {
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_4->setStyleSheet("color:yellow");
        }
    }



    //Setting Background image for TitleScreen Ui - Miguel
    QPixmap bg(":/Background.png");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);
    this->currentOption = 0;
    this->numOptions = 4;
    qApp->installEventFilter(this);
    this->inGame = false;



    //Play sound - Jacari
    QSound::play(qDir.absolutePath() + "/sounds/8bitAudio1.wav");

    this->setFixedSize(800,500);
    this->centerWidget(true);

    mainChar = new Combat_Screen;
    mainChar->set_hero_health(this->_curHealth);
    mainChar->set_attacks(8,20);
    mainChar->set_defend(false);
    mainChar->set_lives(5);
    mainChar->hero_health_bar->setValue(mainChar->get_hero_health());
    // end old MainWindow.cpp
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupGameBoard() {

    this->gridLayout = new QGridLayout;
    this->gridLayout->setHorizontalSpacing(0);
    this->gridLayout->setVerticalSpacing(0);

    this->boardBoundX = 44;
    this->boardBoundY = 44;

    //Instantiating Qimages
    this->_path = QImage(":/PathRecent20x20.png");
    this->_wall = QImage(":/WallRecent20x20.png");
    this->_character = QImage(":/CharacterRecent20x20.png");
    this->_coffin = QImage(":/CoffinRecent20x20.png");              //Considering using this as a pickup item - Miguel

    this->_topLeft = QImage(":/TopLeft.png");                       //Upper Tile
    this->_topMiddle = QImage(":/TopMiddle.png");                   //Upper Tile
    this->_topRight = QImage(":/TopRight.png");                     //Upper Tile

    //Bottom Tiles
    this->_botLeft = QImage(":/BottomLeft.png");
    this->_botRight = QImage(":/BottomRight.png");

    //Left Most Tiles
    this->_midLeft = QImage(":/LeftMiddle.png");
    this->_midRight = QImage(":/RightMiddle.png");
    //Right Most Tiles


    //Define Enemy Map Images
    this->_enemyOne = QImage(":/EnemyMap.png");
    this->_enemyTwo = QImage(":/EnemyMap2.png");
    this->_enemyBoss = QImage(":/EnemyBoss.png");

    for (int y = 0; y <= this->boardBoundY; y++) {
        for (int x = 0; x <= this->boardBoundX; x++) {
            QLabel *textBlock = new QLabel;
            if (y == this->_curY && x == this->_curX) {
                qDebug() << "Found characer!" << endl;
                textBlock->setPixmap(QPixmap::fromImage(this->_character));
            }
            else if (this->boardMatrix[y][x] == 1) {
                textBlock->setPixmap(QPixmap::fromImage(this->_wall));
            }
            else if (this->boardMatrix[y][x] == 2){
                textBlock->setPixmap(QPixmap::fromImage(this->_coffin));

            }
            else if (this->boardMatrix[y][x] == 3){                          //Top left tile
                textBlock->setPixmap(QPixmap::fromImage(this->_topLeft));

            }
            else if (this->boardMatrix[y][x] == 4){                          //Top middle tile
                textBlock->setPixmap(QPixmap::fromImage(this->_topMiddle));

            }
            else if (this->boardMatrix[y][x] == 5){
                textBlock->setPixmap(QPixmap::fromImage(this->_topRight));
            }
            else if (this->boardMatrix[y][x] == 6){
                textBlock->setPixmap(QPixmap::fromImage(this->_botLeft));
            }
            else if (this->boardMatrix[y][x] == 7){
                textBlock->setPixmap(QPixmap::fromImage(this->_botRight));
            }
            else if (this->boardMatrix[y][x] == 8){
                textBlock->setPixmap(QPixmap::fromImage(this->_midLeft));
            }
            else if (this->boardMatrix[y][x] == 9){
                textBlock->setPixmap(QPixmap::fromImage(this->_midRight));
            }

            else if (this->boardMatrix[y][x] == 91){
                textBlock->setPixmap(QPixmap::fromImage(this->_enemyOne));
            }
            else if (this->boardMatrix[y][x] == 93){
                textBlock->setPixmap(QPixmap::fromImage(this->_enemyTwo));
            }
            else if (this->boardMatrix[y][x] == 90){
                textBlock->setPixmap(QPixmap::fromImage(this->_enemyBoss));
            }
            else
                textBlock->setPixmap(QPixmap::fromImage(this->_path));
            gridLayout->addWidget(textBlock, y, x, 1, 1, Qt::AlignCenter);
        }
        QPushButton *backButton = new QPushButton;
        backButton->setText("EXIT");
        backButton->setStyleSheet("background-color:blue; color:yellow; font-family: Terminal; font-size:20px;");
        gridLayout->addWidget(backButton, 46, 0, 1, 5, Qt::AlignCenter | Qt::AlignVCenter);

        QLabel *healthStatusLabel = new QLabel("CURRENT HEALTH: ");
        healthStatusLabel->setStyleSheet("color:yellow; font-family: Terminal; font-size:20px;");
        gridLayout->addWidget(healthStatusLabel, 46, 5, 1, 20, Qt::AlignRight | Qt::AlignVCenter);

        healthStatus = new QLabel("");
        healthStatus->setStyleSheet("color:yellow; font-family: Terminal; font-size:20px;");
        gridLayout->addWidget(healthStatus, 46, 25, 1, 14, Qt::AlignLeft | Qt::AlignVCenter);

        QPushButton *saveButton = new QPushButton("SAVE");
        saveButton->setStyleSheet("background-color:blue; color:yellow; font-family: Terminal; font-size:20px;");
        gridLayout->addWidget(saveButton, 46, 39, 1, 5, Qt::AlignCenter | Qt::AlignVCenter);

        connect(backButton, SIGNAL(clicked()), this, SLOT(on_back_clicked()));
        connect(saveButton, SIGNAL(clicked()), this, SLOT(on_save_clicked()));
    }

    gameBoardWidget = new QWidget;

    this->updateHealth(this->mainChar->get_hero_health());
    gameBoardWidget->setLayout(gridLayout);
    gameBoardWidget->setWindowTitle("Dungeon");
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (this->inGame) {
        menuWidget->setParent(this);
        this->setCentralWidget(menuWidget);
        this->inGame = false;
        this->setFixedSize(800,500);
        QRect screenGeometry = QApplication::desktop()->screenGeometry();
        int x = (screenGeometry.width()-800) / 2;
        int y = (screenGeometry.height()-500) / 2;
        this->move(x, y);


        event->ignore();
    }
    else
        event->accept();
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
    this->SetupGameBoard();
    this->inGame = true;
    this->menuWidget = this->centralWidget();
    if (this->centralWidget())
        this->centralWidget()->setParent(NULL); // Preserve current central widget
    this->setCentralWidget(this->gameBoardWidget);
    this->setFixedSize(900,900);
    this->centerWidget(true);
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
    //Open Title screen through modal approach - Miguel
    //Help_Screen helpScreen;
    //helpScreen.setModal(true);
    //helpScreen.exec();

    //Modalus show screen with heap memory - Miguel
    helpScreenMain = new Help_Screen(this);
    helpScreenMain->show();

    //helpScreen.show();

    return 0;
}

int MainWindow::on_pushButton_4_clicked()
{
    LoadFiles loadGameScreen(this->savedGames.GetSavedGameCount(), this);
    loadGameScreen.setModal(true);
    this->LoadGame(loadGameScreen.exec());
    ui->pushButton->click();
    return 0;
}

int MainWindow::on_back_clicked()
{
    this->close();
    return 0;
}

int MainWindow::on_save_clicked()
{
    if (this->inGame) {
        this->savedGames.AddGame(this->_curX, this->_curY, this->mainChar->get_hero_health());
        this->close();
            return 0;
    }
}




void MainWindow::updateHealth(int health) {
    this->healthStatus->setText(QString::number(health));
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
        this->updateHealth(this->mainChar->get_hero_health());
    } else {
        if (event->key() == Qt::Key_Down) {
            int oldOption = this->currentOption;
            this->currentOption++;
            if (this->currentOption == this->numOptions)
                this->currentOption = 0;
            this->updateMainMenu(oldOption, this->currentOption, false);
            //MainWindow::moveCharacter(MOVE_DOWN);
        }
        else if (event->key() == Qt::Key_Up) {
            int oldOption = this->currentOption;
            this->currentOption = this->currentOption - 1;
            if (this->currentOption == -1) {
                this->currentOption = this->numOptions-1;
            }
            this->updateMainMenu(oldOption, this->currentOption, true);
        } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return  ) {
            if (this->currentOption == 0) {
                ui->pushButton->click();
            } else if (this->currentOption == 1) {
                ui->pushButton_3->click();
            } else if (this->currentOption == 2) {
                ui->pushButton_4->click();
            } else if (this->currentOption == 3) {
                ui->pushButton_2->click();
            }
        }
    }
}

void MainWindow::updateMainMenu(int &oldOption, int &newOption, bool DirectionUp) {


    if (newOption == 2 && !ui->pushButton_4->isEnabled())
    {
        newOption = (DirectionUp ? 1 : 3);
        oldOption = (DirectionUp ? 3 : 1);
    } else if (newOption == 3 && !ui->pushButton_4->isEnabled() && !DirectionUp) {
        oldOption = 1;
    } else if (newOption == 1 && !ui->pushButton_4->isEnabled() && DirectionUp) {
        oldOption = 3;
    }

    qDebug() << (DirectionUp ? "UP" : "DOWN") << "::" << oldOption << ":" << newOption << endl;

    QFont *newFont = new QFont("Terminal", 20, QFont::Bold);
    QFont *oldFont = new QFont("Terminal", 18, QFont::Normal);

    if (newOption == 0) {
        ui->pushButton->setText("[ NEW GAME ]");
        ui->pushButton->setFont(*newFont);
        //ui->pushButton->setStyleSheet("");
    } else if (newOption == 1) {
        ui->pushButton_3->setText("[   HELP   ]");
        ui->pushButton_3->setFont(*newFont);
    } else if (newOption == 2) {
        ui->pushButton_4->setText("[   LOAD   ]");
        ui->pushButton_4->setFont(*newFont);
    } else if (newOption == 3) {
        ui->pushButton_2->setText("[   QUIT   ]");
        ui->pushButton_2->setFont(*newFont);
    }
    if (oldOption == 0) {
        ui->pushButton->setText("NEW GAME");
        ui->pushButton->setFont(*oldFont);
    } else if (oldOption == 1) {
        ui->pushButton_3->setText("HELP");
        ui->pushButton_3->setFont(*oldFont);
    } else if (oldOption == 2) {
        ui->pushButton_4->setText("LOAD");
        ui->pushButton_4->setFont(*oldFont);
    } else if (oldOption == 3) {
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
        if (((_curX - 1) >= 0) && (this->boardMatrix[_curY][_curX-1] != 1)
                && (this->boardMatrix[_curY][_curX-1] != 2)
                && (this->boardMatrix[_curY][_curX-1] != 3)
                && (this->boardMatrix[_curY][_curX-1] != 4)
                && (this->boardMatrix[_curY][_curX-1] != 5)
                && (this->boardMatrix[_curY][_curX-1] != 6)
                && (this->boardMatrix[_curY][_curX-1] != 7)
                && (this->boardMatrix[_curY][_curX-1] != 8)
                && (this->boardMatrix[_curY][_curX-1] != 9)
                && (this->boardMatrix[_curY][_curX-1] != 10)) {
            _curX--;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curX - 1 >= 0 ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_RIGHT) {
        if (((_curX + 1) <= this->boardBoundX)
                && (this->boardMatrix[_curY][_curX+1] != 1)
                && (this->boardMatrix[_curY][_curX+1] != 2)
                && (this->boardMatrix[_curY][_curX+1] != 3)
                && (this->boardMatrix[_curY][_curX+1] != 4)
                && (this->boardMatrix[_curY][_curX+1] != 5)
                && (this->boardMatrix[_curY][_curX+1] != 6)
                && (this->boardMatrix[_curY][_curX+1] != 7)
                && (this->boardMatrix[_curY][_curX+1] != 8)
                && (this->boardMatrix[_curY][_curX+1] != 9)
                && (this->boardMatrix[_curY][_curX+1] != 10)) {
            _curX++;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curX + 1 <= boardBoundX ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_UP) {
        if (((_curY - 1) >= 0)
                && (this->boardMatrix[_curY-1][_curX] != 1)
                && (this->boardMatrix[_curY-1][_curX] != 2)
                && (this->boardMatrix[_curY-1][_curX] != 3)
                && (this->boardMatrix[_curY-1][_curX] != 4)
                && (this->boardMatrix[_curY-1][_curX] != 5)
                && (this->boardMatrix[_curY-1][_curX] != 6)
                && (this->boardMatrix[_curY-1][_curX] != 7)
                && (this->boardMatrix[_curY-1][_curX] != 8)
                && (this->boardMatrix[_curY-1][_curX] != 9)
                && (this->boardMatrix[_curY-1][_curX] != 10)) {
            _curY--;
            moveStatus = MOVE_AUTHORIZED;
        } else
            moveStatus = _curY - 1 >= 0 ? MOVE_ERROR_OUTOFBOUNDS : MOVE_ERROR_BLOCKED;
    } else if (direction == MOVE_DOWN) {
        if (((_curY + 1) <= this->boardBoundY)
                && (this->boardMatrix[_curY+1][_curX] != 1)
                && (this->boardMatrix[_curY+1][_curX] != 2)
                && (this->boardMatrix[_curY+1][_curX] != 3)
                && (this->boardMatrix[_curY+1][_curX] != 4)
                && (this->boardMatrix[_curY+1][_curX] != 5)
                && (this->boardMatrix[_curY+1][_curX] != 6)
                && (this->boardMatrix[_curY+1][_curX] != 7)
                && (this->boardMatrix[_curY+1][_curX] != 8)
                && (this->boardMatrix[_curY+1][_curX] != 9)
                && (this->boardMatrix[_curY+1][_curX] != 10)) {
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
            //set enemy traits
            mainChar->setStandardEnemy(true);
            mainChar->set_enemy_attack(rand()%10+1);
            mainChar->set_enemy_health(40);
            mainChar->enemy_health_display->setNum(mainChar->get_enemy_health());
            mainChar->set_enemy_name("Spider");
            mainChar->setModal(true);
            mainChar->exec();
            //save health and lives-Adam
            this->_curHealth = mainChar->get_hero_health();
            int newLives = mainChar->get_hero_lives();
            //delete previous object
            delete mainChar;
            //restart a new combat situation
            mainChar = new Combat_Screen;
            mainChar->set_hero_health(this->_curHealth);
            mainChar->hero_health_bar->setValue(mainChar->get_hero_health());
            mainChar->set_attacks(8,20);
            mainChar->set_defend(false);
            mainChar->set_lives(newLives);


        }
        if(this->boardMatrix[_curY][_curX]==CHARACTER_BOSS){
            //set boss traits
            std::cout<<mainChar->getStandardEnemy()<<std::endl;
            mainChar->setStandardEnemy(false);
            mainChar->setBossEnemy(true);
            mainChar->setBossHealth();
            mainChar->setMassiveAttack();
            mainChar->setMediumAttack();
            mainChar->setSmallAttack();
            mainChar->set_enemy_health(mainChar->getBossHealth());
            mainChar->setBossName("BOSS");
            mainChar->enemy_health_display->setNum(mainChar->getBossHealth());
            mainChar->setModal(true);
            mainChar->exec();
            //save health and lives-Adam
            this->_curHealth = mainChar->get_hero_health();
            int newLives = mainChar->get_hero_lives();
            //delete previous object
            if(mainChar->Accepted){
                close();
            }
            delete mainChar;


        }
    }
}


void MainWindow::LoadGame(int savedGame) {
    QString data = savedGames.GetSavedGame(savedGame);
    QStringList datas  = data.split(":");
    this->_curX = datas.at(0).toInt();
    this->_curY = datas.at(1).toInt();
    this->_curHealth = datas.at(2).toInt();
}


const int MainWindow::boardMatrix[45][45] = {{3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,2,1,1,0,0,1,1,1,1,1,1,1,1,2,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,2,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,2,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,0,0,0,0,91,0,91,0,91,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,91,93,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,2,0,2,0,2,0,0,2,0,2,0,2,0,2,0,2,1,1,1,1,1,1,9},
                                             {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,9},
                                             {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,9},
                                             {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
                                             {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,90,0},
                                             {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,9},
                                             {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,2,0,2,1,1,1,1,1,1,9},
                                             {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
                                             {6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7}};


