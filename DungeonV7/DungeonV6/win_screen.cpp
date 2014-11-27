#include "win_screen.h"
#include "ui_win_screen.h"
#include <QLayout>

Win_Screen::Win_Screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Win_Screen)
{
    ui->setupUi(this);

    close_button = new QPushButton;
    close_button->setText("CLOSE");
    close_button->setDefault(true);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addStretch();
    main_layout->addWidget(close_button);

    setLayout(main_layout);

    QObject::connect(close_button,SIGNAL(clicked()),
                     this,SLOT(finish()));
}

Win_Screen::~Win_Screen()
{
    delete ui;
}

void Win_Screen::finish(){
    QDialog::done(1);
}
