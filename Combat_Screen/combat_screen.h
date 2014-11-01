
#ifndef COMBAT_SCREEN_H
#define COMBAT_SCREEN_H

#include <QDialog>
#include <QLabel>
#include <QTimer>

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
    QTimer *timer;
    int attack;
    int hero_health;
    int enemy_health;
    const QString enemy_name = "SPIDER   HP";

private slots:
    void calculate_attack();
    void change_value();
    void enable_attack();
};

#endif // COMBAT_SCREEN_H
