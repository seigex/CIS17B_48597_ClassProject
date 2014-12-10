
#ifndef COMBAT_SCREEN_H
#define COMBAT_SCREEN_H

#include <QtGui>
#include "hero.h"
#include <QProgressBar>
#include <QHBoxLayout>
using namespace std;

namespace Ui {
class Combat_Screen;
}

class Combat_Screen : public QDialog,public Hero
{
    Q_OBJECT

public:
    unsigned short atkValue;
    unsigned short dfnValue;
    unsigned short mgcValue;
    void setStandardEnemy(bool n){standardEnemy = n;};
    void setBossEnemy(bool n){bossEnemy = n;};
    bool getStandardEnemy(){return standardEnemy;};
    bool getBossEnemy(){return bossEnemy;};
    QProgressBar *hero_health_bar;
    QLabel *enemy_health_display;
    explicit Combat_Screen(QWidget *parent = 0);
    ~Combat_Screen();

private:
    Ui::Combat_Screen *ui;
    bool standardEnemy;
    bool bossEnemy;
    QPushButton *attack_button;
    QPushButton *defend_button;
    QPushButton *magic_button;
    QPushButton *item_button;
    QLabel *hero_action_label;
    QLabel *enemy_action_label;
    QProgressBar *attack_bar;
    QProgressBar *defend_bar;
    QProgressBar *magic_bar;
    QTimer *attack_timer;
    QTimer *standardAttackTimer;
    QTimer *magic_timer;
    QTimer *defend_timer;
    QTimer *enemy_timer;
    QTimer *enemy_display_timer;
    QTimer *hero_display_timer;
    QTimer *attack_bar_timer;
    QTimer *defend_bar_timer;
    QTimer *magic_bar_timer;
    QTimer *bossTimer;
    void win();
    void lose();

private slots:
    void calculate_attack();
    void enable_attack();
    void enable_magic();
    void enable_defend();
    void calculate_enemy_attack();
    void calculate_standard_attack();
    void set_enemy_action_display();
    void set_hero_action_display();
    void execute_defend();
    void execute_magic();
    void execute_item();
    void update_attack_bar();
    void update_defend_bar();
    void update_magic_bar();
    void bossAttacks();
};

#endif // COMBAT_SCREEN_H
