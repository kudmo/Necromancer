#ifndef LAB3_UNDEAD_H
#define LAB3_UNDEAD_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"
#include "../../../BaseInterfaces/Interfaces/ISummoner.h"

class Undead : public Enemy, public ISummoner {
public:
    Undead(UndeadType& type, FRACTIONS fraction): Enemy(type, fraction) {;};

    void die() override {
        Enemy::die();
    }

    virtual ~Undead() {
        delete type;
    }
};

#endif //LAB3_UNDEAD_H
