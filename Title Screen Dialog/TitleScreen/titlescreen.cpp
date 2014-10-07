#include "titlescreen.h"
#include "ui_titlescreen.h"

TitleScreen::TitleScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TitleScreen)
{

    ui->setupUi(this);

    QPixmap titlePic("C:/Users/agros_000/Pictures/GameTitle.jpg");
    ui->label->setPixmap(titlePic);
}

TitleScreen::~TitleScreen()
{
    delete ui;
}

//Push Button to open the game dialog
void TitleScreen::on_pushButton_clicked()
{
//pending
}

//Push Button to open the loading dialog
void TitleScreen::on_pushButton_2_clicked()
{
//pending
}

//Push button to open the options dialog
void TitleScreen::on_pushButton_3_clicked()
{
//pending
}
