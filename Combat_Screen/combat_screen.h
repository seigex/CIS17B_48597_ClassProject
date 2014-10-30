#ifndef COMBAT_SCREEN_H
#define COMBAT_SCREEN_H

#include <QDialog>

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

private:
    Ui::Combat_Screen *ui;
    QPushButton *attack_button;
    QPushButton *defend_button;
    int attack;
    int hero_health;
    int enemy_health;

private slots:
    void calculate_attack();
};

#endif // COMBAT_SCREEN_H
