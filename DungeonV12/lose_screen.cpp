#include "lose_screen.h"
#include "ui_lose_screen.h"

lose_screen::lose_screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lose_screen)
{
    ui->setupUi(this);
}

lose_screen::~lose_screen()
{
    delete ui;
}

void lose_screen::on_close_button_clicked()
{
    done(1);
}
