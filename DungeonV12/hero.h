#ifndef HERO_H
#define HERO_H

#endif // HERO_H

#include <QLabel>
#include "enemy.h"

class Hero : public Enemy{
public:
    QLabel *hero_pic;
    void set_attacks(int n,int m){attack=5;
                     ice=n;
                     fire=m;};
    void set_lives(int n){lives=n;};
    int get_lives(){return lives;};
    int get_hero_lives(){return lives;};
    void set_hero_health(int n){hero_health=n;};
    void calculate_hero_damage(int damage){hero_health-=damage;};
    int get_hero_health(){return hero_health;};
    int get_hero_attack(){return attack;};
    int get_hero_fire(){return fire;};
    int get_hero_ice(){return ice;};
    bool get_defend(){return defend;};
    void set_defend(bool n){defend=n;};
    void set_enemy_health(int n){enemy_health=n;};
    int get_enemy_health(){return enemy_health;};
    void calculate_enemy_damage(int damage){enemy_health-=damage;};
private:
    int attack;
    int fire;
    int ice;
    bool defend;
    int hero_health;
    int lives;
    int enemy_health;
};
