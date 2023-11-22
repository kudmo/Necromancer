#ifndef LAB3_STONEGOLEMBUILDER_H
#define LAB3_STONEGOLEMBUILDER_H

#include "../GolemBuilder.h"
#include "FireGolem.h"

template <>
class GolemBuilder<FireGolem> {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        FireGolem *type = new FireGolem(level);
        FireGolem *a = new FireGolem(f, coord, type, fraction);
        f.addEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_STONEGOLEMBUILDER_H
