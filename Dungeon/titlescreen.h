#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QDialog>
#include "mainwindow.h"

class TitleScreen : public QDialog
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = 0);
    ~TitleScreen();

private slots:
    int on_pushButton_clicked();
    int on_pushButton_2_clicked();
    int on_pushButton_3_clicked();

private:
    Ui::TitleScreen *ui;
};

#endif // TITLESCREEN_H
