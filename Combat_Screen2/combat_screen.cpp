#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <iostream>
#include <QLabel>
#include <QLayout>
#include <QProgressBar>
#include "combat_screen.h"
#include "win_screen.h"
#include "lose_screen.h"
#include "magic.h"
#include "ui_combat_screen.h"

Combat_Screen::Combat_Screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Combat_Screen)
{
    ui->setupUi(this);

    set_hero_lives(5);
    set_enemy_health(40);
    set_hero_health(100);
    set_attacks(8,20);
    set_defend(false);

    enemy_display_timer = new QTimer;
    hero_display_timer = new QTimer;
    defend_timer = new QTimer;
    magic_timer = new QTimer;
    attack_timer = new QTimer;
    enemy_timer = new QTimer;

    hero_action_label = new QLabel;
    enemy_action_label = new QLabel;

    enemy_health_display = new QLabel;
    enemy_health_display->setNum(get_enemy_health());

    attack_button = new QPushButton;
    attack_button->setText("ATTACK");
    attack_button->setDefault(true);

    defend_button = new QPushButton;
    defend_button->setText("DEFEND");

    magic_button = new QPushButton;
    magic_button->setText("MAGIC");

    hero_health_bar = new QProgressBar;
    hero_health_bar->setValue(get_hero_health());

    QVBoxLayout *left_layout = new QVBoxLayout;
    left_layout->addWidget(hero_health_bar);
    left_layout->addSpacing(100);
    left_layout->addWidget(attack_button);
    left_layout->addWidget(magic_button);
    left_layout->addWidget(defend_button);

    QLabel *enemy_title = new QLabel;
    QLabel *hp_label = new QLabel;
    enemy_title->setText(enemy_name);
    hp_label->setText(" HP");

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

    enemy_timer->start(6000);

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(calculate_attack()));
    QObject::connect(enemy_timer,SIGNAL(timeout()),
                     this,SLOT(calculate_enemy_attack()));
    QObject::connect(defend_button,SIGNAL(clicked()),
                     this,SLOT(execute_defend()));
    QObject::connect(magic_button,SIGNAL(clicked()),
                     this,SLOT(execute_magic()));


}

Combat_Screen::~Combat_Screen()
{
    delete ui;
}

void Combat_Screen::calculate_attack(){
    hero_display_timer->stop();
    calculate_enemy_damage(get_hero_attack());
    enemy_health_display->setNum(get_enemy_health());

    if(get_enemy_health()<=0){
        hero_action_label->hide();
        enemy_action_label->hide();
        enemy_timer->stop();
        Win_Screen *dialog = new Win_Screen;
        if(dialog->exec()==1){
            close();
        }
    }

    attack_button->setEnabled(false);
    attack_timer->start(6000);
    hero_display_timer->start(3000);

    hero_action_label->setText("You used ATTACK! -5");

    QObject::connect(hero_display_timer,SIGNAL(timeout()),
                     this,SLOT(set_hero_action_display()));

    QObject::connect(attack_timer,SIGNAL(timeout()),
                     this,SLOT(enable_attack()));

    hero_action_label->show();

}

void Combat_Screen::execute_magic(){
    Magic *magic_dialog = new Magic;
    int n=magic_dialog->exec();
    if(n==1){
        hero_display_timer->stop();
        calculate_enemy_damage(get_hero_fire());
        hero_action_label->setText("You used FIRE -20");
        hero_action_label->show();
        enemy_health_display->setNum(get_enemy_health());
        magic_button->setEnabled(false);
        magic_timer->start(25000);
        hero_display_timer->start(3000);

        QObject::connect(hero_display_timer,SIGNAL(timeout()),
                         this,SLOT(set_hero_action_display()));

    }if(n==2){
        calculate_enemy_damage(get_hero_ice());
        hero_action_label->setText("You used ICE -8");
        hero_action_label->show();
        hero_display_timer->stop();
        enemy_health_display->setNum(get_enemy_health());
        magic_button->setEnabled(false);
        magic_timer->start(25000);
        hero_display_timer->start(3000);

        QObject::connect(hero_display_timer,SIGNAL(timeout()),
                         this,SLOT(set_hero_action_display()));
    }
    QObject::connect(magic_timer,SIGNAL(timeout()),
                     this,SLOT(enable_magic()));
    if(get_enemy_health()<=0){
        set_enemy_health(0);
        enemy_health_display->setNum(get_enemy_health());
        hero_action_label->hide();
        enemy_action_label->hide();
        enemy_timer->stop();
        magic_timer->stop();
        Win_Screen *dialog = new Win_Screen;
        if(dialog->exec()==1){
            close();
        }
    }
}

void Combat_Screen::execute_defend(){
    defend_timer->start(10000);
    set_defend(true);
    defend_button->setEnabled(false);

    QObject::connect(defend_timer,SIGNAL(timeout()),
                     this,SLOT(enable_defend()));


}

void Combat_Screen::calculate_enemy_attack(){

    if(get_defend()==true){
        enemy_action_label->setText("SPIDER used BITE! -0");
        enemy_action_label->show();

        enemy_display_timer->start(3000);

        hero_action_label->setText("you defended the attack!");
        hero_action_label->show();

        hero_display_timer->start(3000);

        set_defend(false);
    }else{
    calculate_hero_damage(5);
    hero_health_bar->setValue(get_hero_health());
    enemy_action_label->setText("SPIDER used BITE! -5");
    enemy_action_label->show();
    enemy_display_timer->start(5000);
    if(get_hero_health()<=0){
        hero_health_bar->setValue(0);
        hero_action_label->hide();
        enemy_action_label->hide();
        enemy_timer->stop();
        magic_timer->stop();
        lose_screen *dialog = new lose_screen;
        set_hero_lives(get_hero_lives()-1);
        if(dialog->exec()==1){
            close();
        }
    }
}
    QObject::connect(enemy_display_timer,SIGNAL(timeout()),
                     this,SLOT(set_enemy_action_display()));
    QObject::connect(hero_display_timer,SIGNAL(timeout()),
                     this,SLOT(set_hero_action_display()));


}

void Combat_Screen::enable_attack(){

    attack_button->setEnabled(true);
    attack_timer->stop();

}

void Combat_Screen::enable_magic(){
    magic_button->setEnabled(true);
    magic_timer->stop();
}

void Combat_Screen::enable_defend(){

    defend_button->setEnabled(true);
    defend_timer->stop();

}

void Combat_Screen::set_enemy_action_display(){
    enemy_action_label->hide();
    enemy_display_timer->stop();
}

void Combat_Screen::set_hero_action_display(){
    hero_action_label->hide();
    hero_display_timer->stop();
}
