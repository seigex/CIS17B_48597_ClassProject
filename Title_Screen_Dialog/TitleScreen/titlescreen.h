#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QDialog>

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QDialog
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = 0);
    ~TitleScreen();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::TitleScreen *ui;
};

#endif // TITLESCREEN_H
