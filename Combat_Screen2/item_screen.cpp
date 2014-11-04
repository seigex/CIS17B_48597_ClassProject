#include "item_screen.h"
#include "ui_item_screen.h"

Item_screen::Item_screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Item_screen)
{
    ui->setupUi(this);
}

Item_screen::~Item_screen()
{
    delete ui;
}

void Item_screen::on_pushButton_clicked()
{
    done(1);
}

void Item_screen::on_pushButton_2_clicked()
{
    done(2);
}

void Item_screen::on_pushButton_3_clicked()
{
    done(3);
}

void Item_screen::on_pushButton_4_clicked()
{
    done(4);
}
