#ifndef LAB3_ALIVE_H
#define LAB3_ALIVE_H

#include <utility>

#include "../../../BaseInterfaces/Interfaces/ISummoner.h"

#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"

#include "../../UserEnemyTypes/AliveType/AliveType.h"
#include "../../UserItems/DeadBody/DeadBody.h"

class Alive : public Enemy, public ISummoner {
public:
    Alive(Floor& f, std::pair<size_t,size_t> coord, AliveType* type, FRACTIONS fraction);

    void die() override;
};

#endif //LAB3_ALIVE_H
