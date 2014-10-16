#include "titlescreen.h"


TitleScreen::TitleScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TitleScreen)
{

    ui->setupUi(this);

    //FIXME: Hardcoded title needs to be a resource and wasn't included in zip.
    //QPixmap titlePic("C:/Users/agros_000/Pictures/GameTitle.jpg");
    //ui->label->setPixmap(titlePic);
}

TitleScreen::~TitleScreen()
{
    delete ui;
}

//Push Button to open the game dialog
int TitleScreen::on_pushButton_clicked()
{
    this->done(1);
}

//Push Button to open the loading dialog
int TitleScreen::on_pushButton_2_clicked()
{
        this->done(2);
}

//Push button to open the options dialog
int TitleScreen::on_pushButton_3_clicked()
{
    this->done(3);
}
