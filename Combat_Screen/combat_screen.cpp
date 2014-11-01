#include <QPushButton>
#include <QTimer>
#include <iostream>
#include <QLabel>
#include <QLayout>
#include <QProgressBar>
#include "combat_screen.h"
#include "win_screen.h"
#include "ui_combat_screen.h"

Combat_Screen::Combat_Screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Combat_Screen)
{
    ui->setupUi(this);

    set_health();

    set_attack();

    timer = new QTimer;

    enemy_health_display = new QLabel;
    enemy_health_display->setNum(enemy_health);

    attack_button = new QPushButton;
    attack_button->setText("ATTACK");
    attack_button->setDefault(true);

    defend_button = new QPushButton;
    defend_button->setText("DEFEND");

    QProgressBar *hero_health_bar = new QProgressBar;
    hero_health_bar->setValue(hero_health);

    QVBoxLayout *left_layout = new QVBoxLayout;
    left_layout->addWidget(hero_health_bar);
    left_layout->addSpacing(100);
    left_layout->addWidget(attack_button);
    left_layout->addWidget(defend_button);

    QLabel *enemy_title = new QLabel;
    enemy_title->setText(enemy_name);

    QHBoxLayout *top_right_layout = new QHBoxLayout;
    top_right_layout->addWidget(enemy_title);
    top_right_layout->addWidget(enemy_health_display);

    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->addLayout(top_right_layout);
    right_layout->addStretch();

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addLayout(left_layout);
    main_layout->addSpacing(100);
    main_layout->addLayout(right_layout);

    setLayout(main_layout);

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(calculate_attack()));

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(change_value()));

}

Combat_Screen::~Combat_Screen()
{
    delete ui;
}

void Combat_Screen::calculate_attack(){
    enemy_health=enemy_health-attack;


    if(enemy_health<=0){
        Win_Screen *dialog = new Win_Screen;
        dialog->show();

        QObject::connect(dialog,SIGNAL(finished(int)),
                         this,SLOT(close()));
    }

    attack_button->setEnabled(false);

    timer->start(10000);

    QObject::connect(timer,SIGNAL(timeout()),
                     this,SLOT(enable_attack()));

}


void Combat_Screen::change_value(){

    enemy_health_display->setNum(enemy_health);

}

void Combat_Screen::enable_attack(){

    attack_button->setEnabled(true);

}

