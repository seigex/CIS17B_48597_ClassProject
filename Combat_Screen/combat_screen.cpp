#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include "combat_screen.h"
#include "ui_combat_screen.h"

Combat_Screen::Combat_Screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Combat_Screen)
{
    ui->setupUi(this);

    attack_button = new QPushButton;
    attack_button->setText("ATTACK");
    attack_button->setDefault(true);

    defend_button = new QPushButton;
    defend_button->setText("DEFEND");

    QVBoxLayout *bottom_left_layout = new QVBoxLayout;
    bottom_left_layout->addSpacing(200);
    bottom_left_layout->addWidget(attack_button);
    bottom_left_layout->addWidget(defend_button);

    QHBoxLayout *left_layout = new QHBoxLayout;
    left_layout->addLayout(bottom_left_layout);
    left_layout->addSpacing(200);


    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(left_layout);

    setLayout(main_layout);

    QObject::connect(attack_button,SIGNAL(clicked()),
                     this,SLOT(calculate_attack()));

    set_health();

    if(enemy_health<=0){
        close();
    }
}

Combat_Screen::~Combat_Screen()
{
    delete ui;
}

void Combat_Screen::calculate_attack(){
    enemy_health=enemy_health-attack;
}


