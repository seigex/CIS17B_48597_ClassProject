#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include <QMainWindow>


namespace Ui {
class Help_Screen;
}

class Help_Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Help_Screen(QWidget *parent = 0);
    ~Help_Screen();

private slots:
    void on_ReturnToMain_clicked();

    void on_ReturnToMain_pressed();

private:
    Ui::Help_Screen *ui;
};

#endif // HELP_SCREEN_H
