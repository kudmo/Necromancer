#ifndef LAB3_GOLEM_H
#define LAB3_GOLEM_H

#include <cstdlib>
#include <ctime>
#include <random>

#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"

#include "../../UserEnemyTypes/GolemType/GolemType.h"

class Golem : public  Enemy {
public:
    Golem(Floor& f, std::pair<size_t,size_t> coord, GolemType* type, FRACTIONS fraction);

    uint getIgnoringProbability() const;
    uint damaged(IAttacker &attacker, uint damage) override;

    void die() override;
};
#endif //LAB3_GOLEM_H
