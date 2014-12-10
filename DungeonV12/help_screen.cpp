#include "help_screen.h"
#include "ui_help_screen.h"
#include <QDialog>

Help_Screen::Help_Screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help_Screen)
{

    ui->setupUi(this);

    //Setting Background image for TitleScreen Ui - Miguel
    QPixmap bg(":/Background.png");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);

}

Help_Screen::~Help_Screen()
{
    delete ui;
}

void Help_Screen::on_ReturnToMain_clicked()
{
    this->close();
}

void Help_Screen::on_ReturnToMain_pressed()
{
    this->close();
}
