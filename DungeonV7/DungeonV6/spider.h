#ifndef SPIDER_H
#define SPIDER_H
#include "enemy.h"

#endif // SPIDER_H

class Spider : public Enemy{
public:
    Spider(){//do nothing};
    virtual int generic_attack(){return 5;};
private:
    void bite_attack();
    void web_attack();
};
