#ifndef ENEMY_H
#define ENEMY_H
#include <QtGui>

#endif // ENEMY_H

class Enemy{
public:
    Enemy();
    void set_enemy_health(int n){enemy_health=n;}
    int get_enemy_health(){return enemy_health;}
    virtual int generic_attack();
    //void set_enemy_name(QString n){enemy_name(n);};
    //QString get_enemy_name(){return set_enemy_name();};
private:
    int enemy_health;
    QString enemy_name;
};
