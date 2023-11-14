#ifndef LAB3_GOLEM_H
#define LAB3_GOLEM_H

#include <cstdlib>
#include <ctime>
#include <random>

#include "../../UserEnemyTypes/GolemType/GolemType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"

class Golem : public  Enemy {
public:
    //!@todo Конструктор?? или фабрика)
    uint getIgnoringProbability() const;
    uint damaged(IAttacker &attacker, uint damage) override {
        srand(time(0));
        uint p = abs(rand()) % 100;
        if (p > getIgnoringProbability()) {
            Enemy::damaged(attacker, damage);
        }
    }

    void die() overrided {
        Enemy::die();
    }

    virtual ~Golem() {
        delete type;
    }
};
#endif //LAB3_GOLEM_H
