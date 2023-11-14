#ifndef LAB3_ALIVE_H
#define LAB3_ALIVE_H

#include <utility>

#include "../../UserEnemyTypes/AliveType/AliveType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"
#include "../../UserItems/DeadBody/DeadBody.h"
#include "../../../BaseInterfaces/Interfaces/ISummoner.h"

class Alive : public Enemy, public ISummoner {
public:
    Alive(AliveType& type, FRACTIONS fraction): Enemy(type, fraction) {};

    void die() override {
        Field& position = this->getPosition();
        auto body = new DeadBody(dynamic_cast<AliveType*>(this->type));
        position.addItem(*body);
        Enemy::die();
    }
};

#endif //LAB3_ALIVE_H
