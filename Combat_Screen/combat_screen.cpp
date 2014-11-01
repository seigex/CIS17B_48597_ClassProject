#include <QPushButton>
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

    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->addWidget(enemy_health_display);
    right_layout->addStretch();

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addLayout(left_layout);
    main_layout->addSpacing(100);
    main_layout->addLayout(right_layout);

    setLayout(main_layout);

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(calculate_attack()));

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(show_output()));

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
}

void Combat_Screen::show_output(){
    std::cout<<enemy_health<<std::endl;
}

void Combat_Screen::change_value(){
    enemy_health_display->setNum(enemy_health);
}

