#include <QtGui>
#include <iostream>
#include "combat_screen.h"
#include "win_screen.h"
#include "lose_screen.h"
#include "magic.h"
#include "item_screen.h"
#include "ui_combat_screen.h"

Combat_Screen::Combat_Screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Combat_Screen)
{
    ui->setupUi(this);

    set_lives(1);
    set_enemy_health(40);
    set_hero_health(100);
    set_attacks(8,20);
    set_defend(false);
    atkValue=0;
    dfnValue=0;
    mgcValue=0;
    QImage hero;
    hero = QImage("C:/Users/agros_000/Desktop/push/Combat_Screen2/Character.png");
    hero_pic = new QLabel;
    hero_pic->setPixmap(QPixmap::fromImage(hero));

    QLabel *enemy_title = new QLabel;
    QLabel *hp_label = new QLabel;
    enemy_title->setText("SPIDER ");
    hp_label->setText(" HP");

    enemy_display_timer = new QTimer;
    hero_display_timer = new QTimer;
    defend_timer = new QTimer;
    magic_timer = new QTimer;
    attack_timer = new QTimer;
    enemy_timer = new QTimer;

    hero_action_label = new QLabel;
    hero_action_label->setText(" ");
    enemy_action_label = new QLabel;
    enemy_action_label->setText(" ");

    enemy_health_display = new QLabel;
    enemy_health_display->setNum(get_enemy_health());

    attack_button = new QPushButton;
    attack_button->setText("ATTACK");
    attack_button->setDefault(true);

    defend_button = new QPushButton;
    defend_button->setText("DEFEND");

    magic_button = new QPushButton;
    magic_button->setText("MAGIC");

    item_button = new QPushButton;
    item_button->setText("ITEM");

    hero_health_bar = new QProgressBar;
    hero_health_bar->setValue(get_hero_health());
    QString mainStyleSheet = QString("QProgressBar::chunk { background: green;}");
    mainStyleSheet.append("QProgressBar{ color: black;}");
    mainStyleSheet.append("QProgressBar {border: 2px solid grey; text-align: center; background-color: grey;}");
    hero_health_bar->setStyleSheet(mainStyleSheet);
    attack_bar = new QProgressBar;
    QString myStyleSheet1 = QString("QProgressBar::chunk { background: purple;}");
    myStyleSheet1.append("QProgressBar{ color: black;}");
    myStyleSheet1.append("QProgressBar {border: 1px solid grey; text-align: center; background-color: grey;}");
    attack_bar->setStyleSheet(myStyleSheet1);
    defend_bar = new QProgressBar;
    QString myStyleSheet2 = QString("QProgressBar::chunk { background: yellow;}");
    myStyleSheet2.append("QProgressBar{ color: black;}");
    myStyleSheet2.append("QProgressBar {border: 1px solid grey; text-align: center; background-color: grey;}");
    defend_bar->setStyleSheet(myStyleSheet2);
    magic_bar = new QProgressBar;
    QString myStyleSheet3 = QString("QProgressBar::chunk { background: blue;}");
    myStyleSheet3.append("QProgressBar{ color: black;}");
    myStyleSheet3.append("QProgressBar {border: 1px solid grey; text-align: center; background-color: grey;}");
    magic_bar->setStyleSheet(myStyleSheet3);
    attack_bar->setValue(atkValue);
    defend_bar->setValue(dfnValue);
    magic_bar->setValue(mgcValue);

    QHBoxLayout *attack_button_layout = new QHBoxLayout;
    attack_button_layout->addWidget(attack_button);
    attack_button_layout->addWidget(attack_bar);

    QHBoxLayout *defend_button_layout = new QHBoxLayout;
    defend_button_layout->addWidget(defend_button);
    defend_button_layout->addWidget(defend_bar);

    QHBoxLayout *magic_button_layout = new QHBoxLayout;
    magic_button_layout->addWidget(magic_button);
    magic_button_layout->addWidget(magic_bar);

    QHBoxLayout *item_button_layout = new QHBoxLayout;
    item_button_layout->addWidget(item_button);

    QVBoxLayout *left_layout = new QVBoxLayout;
    left_layout->addWidget(hero_health_bar);
    left_layout->addWidget(hero_pic);
    left_layout->addLayout(attack_button_layout);
    left_layout->addLayout(defend_button_layout);
    left_layout->addLayout(magic_button_layout);
    left_layout->addLayout(item_button_layout);

    QHBoxLayout *top_right_layout = new QHBoxLayout;
    top_right_layout->addWidget(enemy_title);
    top_right_layout->addWidget(hp_label);
    top_right_layout->addWidget(enemy_health_display);

    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->addLayout(top_right_layout);
    right_layout->addStretch();

    QHBoxLayout *top_layout = new QHBoxLayout;
    top_layout->addLayout(left_layout);
    top_layout->addSpacing(100);
    top_layout->addLayout(right_layout);

    QVBoxLayout *bottom_layout = new QVBoxLayout;
    bottom_layout->addWidget(hero_action_label);
    bottom_layout->addWidget(enemy_action_label);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);

    setLayout(main_layout);

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(calculate_attack()));
    QObject::connect(enemy_timer,SIGNAL(timeout()),
                     this,SLOT(calculate_enemy_attack()));
    QObject::connect(defend_button,SIGNAL(clicked()),
                     this,SLOT(execute_defend()));
    QObject::connect(magic_button,SIGNAL(clicked()),
                     this,SLOT(execute_magic()));
    QObject::connect(item_button,SIGNAL(clicked()),
                     this,SLOT(execute_item()));

    hero_action_label->show();
    enemy_action_label->show();
    enemy_timer->start(6000);

}

Combat_Screen::~Combat_Screen()
{
    delete ui;
}

void Combat_Screen::calculate_attack(){

    calculate_enemy_damage(get_hero_attack());
    enemy_health_display->setNum(get_enemy_health());

    if(get_enemy_health()<=0){
        win();
        Win_Screen dialog(this);
        if(dialog.exec()==1){
            close();
        }
    }

    attack_bar_timer = new QTimer;

    QObject::connect(attack_bar_timer,SIGNAL(timeout()),
                     this,SLOT(update_attack_bar()));
    QObject::connect(hero_display_timer,SIGNAL(timeout()),
                     this,SLOT(set_hero_action_display()));
    QObject::connect(attack_timer,SIGNAL(timeout()),
                     this,SLOT(enable_attack()));

    attack_button->setEnabled(false);
    attack_timer->start(6000);
    attack_bar_timer->start(50);
    hero_display_timer->start(3000);
    hero_action_label->setText("You used ATTACK! -5");
    hero_action_label->show();

}

void Combat_Screen::execute_magic(){

    //Create and execute the magic menu dialog and set an integer to hold the value returned
    Magic *magic_dialog = new Magic;
    int n=magic_dialog->exec();
    //if the fire button is cliced a 1 is returned
    if(n==1){
        calculate_enemy_damage(get_hero_fire());
        hero_action_label->setText("You used FIRE -20");
        enemy_health_display->setNum(get_enemy_health());

        QObject::connect(hero_display_timer,SIGNAL(timeout()),
                         this,SLOT(set_hero_action_display()));

        magic_button->setEnabled(false);
        magic_timer->start(25000);
        hero_display_timer->start(3000);

    }if(n==2){
        calculate_enemy_damage(get_hero_ice());
        hero_action_label->setText("You used ICE -8");
        enemy_health_display->setNum(get_enemy_health());

        QObject::connect(hero_display_timer,SIGNAL(timeout()),
                         this,SLOT(set_hero_action_display()));

        magic_button->setEnabled(false);
        magic_timer->start(25000);
        hero_display_timer->start(3000);

    }

    magic_bar_timer = new QTimer;

    QObject::connect(magic_timer,SIGNAL(timeout()),
                     this,SLOT(enable_magic()));
    QObject::connect(magic_bar_timer,SIGNAL(timeout()),
                     this,SLOT(update_magic_bar()));
    magic_bar_timer->start(242);

    if(get_enemy_health()<=0){
        win();
        Win_Screen dialog(this);
        if(dialog.exec()==1){
            close();
        }
    }
}

void Combat_Screen::execute_defend(){

    defend_bar_timer = new QTimer;

    QObject::connect(defend_timer,SIGNAL(timeout()),
                     this,SLOT(enable_defend()));

    QObject::connect(defend_bar_timer,SIGNAL(timeout()),
                     this,SLOT(update_defend_bar()));

    defend_bar_timer->start(94);
    defend_timer->start(10000);
    set_defend(true);
    defend_button->setEnabled(false);

}

void Combat_Screen::execute_item(){
    Item_screen *dialog = new Item_screen;
    int n=dialog->exec();
}

void Combat_Screen::calculate_enemy_attack(){

    QObject::connect(enemy_display_timer,SIGNAL(timeout()),
                     this,SLOT(set_enemy_action_display()));
    QObject::connect(hero_display_timer,SIGNAL(timeout()),
                     this,SLOT(set_hero_action_display()));

    if(get_defend()==true){

        enemy_action_label->setText("SPIDER used BITE! -0");
        hero_action_label->setText("you defended the attack!");
        enemy_display_timer->start(3000);
        hero_display_timer->start(3000);
        set_defend(false);

    }else{

    calculate_hero_damage(5);
    hero_health_bar->setValue(get_hero_health());
    enemy_action_label->setText("SPIDER used BITE! -5");
    enemy_display_timer->start(3000);

    if(get_hero_health()<=0){
        lose_screen dialog(this);
        set_lives(get_lives()-1);
        if(dialog.exec()==1){
            if(get_lives()==0){
                std::cout<<"YOU LOSE!"<<std::endl;
            }
            close();
        }
    }
}
}

void Combat_Screen::enable_attack(){

    atkValue=0;
    attack_bar->setValue(atkValue);
    delete attack_bar_timer;
    attack_bar_timer = NULL;
    attack_button->setEnabled(true);
    attack_timer->stop();

}

void Combat_Screen::enable_magic(){
    mgcValue=0;
    magic_bar->setValue(mgcValue);
    delete magic_bar_timer;
    magic_bar_timer = NULL;
    magic_button->setEnabled(true);
    magic_timer->stop();
}

void Combat_Screen::enable_defend(){
    dfnValue=0;
    defend_bar->setValue(dfnValue);
    delete defend_bar_timer;
    defend_bar_timer = NULL;
    defend_button->setEnabled(true);
    defend_timer->stop();

}

void Combat_Screen::set_enemy_action_display(){
    enemy_action_label->setText(" ");
    enemy_display_timer->stop();
}

void Combat_Screen::set_hero_action_display(){
    hero_action_label->setText(" ");
    hero_display_timer->stop();
}

void Combat_Screen::update_attack_bar(){
    atkValue++;
    attack_bar->setValue(atkValue);
}

void Combat_Screen::update_defend_bar(){
    dfnValue++;
    defend_bar->setValue(dfnValue);
}

void Combat_Screen::update_magic_bar(){
    mgcValue++;
    magic_bar->setValue(mgcValue);
}

void Combat_Screen::win(){
    set_enemy_health(0);
    enemy_health_display->setNum(get_enemy_health());
    hero_action_label->setText(" ");
    enemy_action_label->setText(" ");
    attack_button->setEnabled(true);
    defend_button->setEnabled(true);
    magic_button->setEnabled(true);
    item_button->setEnabled(true);
    magic_timer->stop();
    attack_timer->stop();
    enemy_timer->stop();
    defend_timer->stop();
    enemy_display_timer->stop();
    hero_display_timer->stop();
    delete attack_bar_timer;
    attack_bar_timer = NULL;
    delete defend_bar_timer;
    defend_bar_timer = NULL;
    delete magic_bar_timer;
    magic_bar_timer = NULL;
    attack_bar->setValue(0);
    defend_bar->setValue(0);
    magic_bar->setValue(0);
}

void Combat_Screen::lose(){
    set_hero_health(0);
    hero_health_bar->setValue(get_hero_health());
    hero_action_label->setText(" ");
    enemy_action_label->setText(" ");
    attack_button->setEnabled(true);
    defend_button->setEnabled(true);
    magic_button->setEnabled(true);
    item_button->setEnabled(true);
    magic_timer->stop();
    attack_timer->stop();
    attack_timer->stop();
    defend_timer->stop();
    enemy_display_timer->stop();
    hero_display_timer->stop();
    delete attack_bar_timer;
    attack_bar_timer = NULL;
    delete defend_bar_timer;
    defend_bar_timer = NULL;
    delete magic_bar_timer;
    magic_bar_timer = NULL;
    attack_bar->setValue(0);
    defend_bar->setValue(0);
    magic_bar->setValue(0);
}
