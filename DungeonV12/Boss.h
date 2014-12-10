#ifndef BOSS_H
#define BOSS_H

#include <QString>

class Boss{
public:
    void setBossHealth(){bossHealth=100;}
    void setMassiveAttack(){massiveDamage=20;};
    void setMediumAttack(){mediumDamage=10;};
    void setSmallAttack(){smallDamage=5;};
    int getBossHealth(){return bossHealth;}
    int getMassiveAttack(){return massiveDamage;};
    int getMediumAttack(){return mediumDamage;};
    int getSmallAttack(){return smallDamage;};
    void setBossName(QString n){bossName.append(n);};
    QString getBossName(){return bossName;};
private:
    int massiveDamage;
    int mediumDamage;
    int smallDamage;
    int bossHealth;
    QString bossName;

};

#endif // BOSS_H
