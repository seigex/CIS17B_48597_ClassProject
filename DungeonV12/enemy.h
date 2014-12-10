#ifndef ENEMY_H
#define ENEMY_H
#include <QtGui>
#include "Boss.h"

#endif // ENEMY_H

class Enemy : public Boss{
public:
    void set_enemy_health(int n){enemy_health=n;}
    void set_enemy_attack(int n){enemy_attack=n;};
    int get_enemy_health(){return enemy_health;}
    int get_enemy_attack(){return enemy_attack;};
    void set_enemy_name(QString n){enemy_name.append(n);};
    QString get_enemy_name(){return enemy_name;};
private:
    int enemy_health;
    QString enemy_name;
    int enemy_attack;
};
