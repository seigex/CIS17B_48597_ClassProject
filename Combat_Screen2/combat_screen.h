
#ifndef COMBAT_SCREEN_H
#define COMBAT_SCREEN_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QProgressBar>
#include "magic.h"


namespace Ui {
class Combat_Screen;
}

class Combat_Screen : public QDialog, public Hero
{
    Q_OBJECT

public:
    explicit Combat_Screen(QWidget *parent = 0);
    ~Combat_Screen();

private:
    Ui::Combat_Screen *ui;
    QPushButton *attack_button;
    QPushButton *defend_button;
    QPushButton *magic_button;
    QPushButton *item_button;
    QLabel *enemy_health_display;
    QLabel *hero_action_label;
    QLabel *enemy_action_label;
    QProgressBar *hero_health_bar;
    QProgressBar *attack_bar;
    QProgressBar *defend_bar;
    QProgressBar *magic_bar;
    QTimer *attack_timer;
    QTimer *magic_timer;
    QTimer *defend_timer;
    QTimer *enemy_timer;
    QTimer *enemy_display_timer;
    QTimer *hero_display_timer;

private slots:
    void calculate_attack();
    void enable_attack();
    void enable_magic();
    void enable_defend();
    void calculate_enemy_attack();
    void set_enemy_action_display();
    void set_hero_action_display();
    void execute_defend();
    void execute_magic();
    void execute_item();
};

#endif // COMBAT_SCREEN_H
