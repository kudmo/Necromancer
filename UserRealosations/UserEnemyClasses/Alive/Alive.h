#ifndef LAB3_ALIVE_H
#define LAB3_ALIVE_H

#include <utility>

#include "../../UserEnemyTypes/AliveType/AliveType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"

class Alive : public Enemy {
public:
    Alive(AliveType*);
    void die() override;
};
#endif //LAB3_ALIVE_H
