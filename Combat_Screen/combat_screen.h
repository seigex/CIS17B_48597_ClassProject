
#ifndef COMBAT_SCREEN_H
#define COMBAT_SCREEN_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QProgressBar>

namespace Ui {
class Combat_Screen;
}

class Combat_Screen : public QDialog
{
    Q_OBJECT

public:
    explicit Combat_Screen(QWidget *parent = 0);
    ~Combat_Screen();
    void set_health(){
        hero_health=100;
        enemy_health=20;};
    void set_attack(){attack=5;};
    int get_enemy_health(){return enemy_health;};

private:
    Ui::Combat_Screen *ui;
    QPushButton *attack_button;
    QPushButton *defend_button;
    QLabel *enemy_health_display;
    QLabel *hero_action_label;
    QLabel *enemy_action_label;
    QProgressBar *hero_health_bar;
    QTimer *attack_timer;
    QTimer *enemy_timer;
    int attack;
    int hero_health;
    int enemy_health;
    const QString enemy_name = "SPIDER ";

private slots:
    void calculate_attack();
    void change_value();
    void enable_attack();
    void calculate_enemy_attack();
    void set_enemy_action_display();
    void set_hero_action_display();
};

#endif // COMBAT_SCREEN_H
