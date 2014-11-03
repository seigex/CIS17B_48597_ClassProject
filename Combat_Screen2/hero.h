#ifndef HERO_H
#define HERO_H

#endif // HERO_H

class Hero{
public:
    Hero(){//do nothing
        };
    bool fire_used=false;
    bool ice_used=false;
    void set_attack(){attack=5;};
    void set_hero_health(){hero_health=100;};
    void calculate_hero_damage(int damage){hero_health-=damage;};
    int get_hero_health(){return hero_health;};
    int get_hero_attack(){return attack;};
    bool get_defend(){return defend;};
    void set_defend(bool n){defend=n;};
    void set_enemy_health(){enemy_health=40;};
    int get_enemy_health(){return enemy_health;};
    void calculate_enemy_damage(int damage){enemy_health-=damage;};
private:
    int attack;
    bool defend;
    int hero_health;
    int enemy_health;
};
