#include "loadfiles.h"
#include "ui_loadfiles.h"

LoadFiles::LoadFiles(int savedGameCount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFiles)
{
    ui->setupUi(this);

    for (int i = 0; i < savedGameCount; i++) {
        QString item("SAVED GAME %1");
        ui->listWidget->addItem(item.arg(i));
    }
}

LoadFiles::~LoadFiles()
{
    delete ui;
}

void LoadFiles::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    this->done(item->listWidget()->row(item));
}
