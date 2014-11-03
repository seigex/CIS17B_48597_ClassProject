#include <QPushButton>
#include <QLayout>
#include "magic.h"
#include "ui_magic.h"

Magic::Magic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Magic)
{
    ui->setupUi(this);

    fire_button = new QPushButton;
    fire_button->setText("FIRE");
    ice_button = new QPushButton;
    ice_button->setText("ICE");
    close_button = new QPushButton;
    close_button->setText("CLOSE");

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(fire_button);
    button_layout->addWidget(ice_button);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addStretch();
    main_layout->addLayout(button_layout);
    main_layout->addWidget(close_button);

    setLayout(main_layout);

    QObject::connect(fire_button,SIGNAL(clicked()),
                     this,SLOT(execute_fire()));
    QObject::connect(ice_button,SIGNAL(clicked()),
                     this,SLOT(execute_ice()));
    QObject::connect(close_button,SIGNAL(clicked()),
                     this,SLOT(close()));

}

Magic::~Magic()
{
    delete ui;
}

void Magic::execute_fire(){
    QDialog::done(1);
}

void Magic::execute_ice(){
    QDialog::done(2);
}

