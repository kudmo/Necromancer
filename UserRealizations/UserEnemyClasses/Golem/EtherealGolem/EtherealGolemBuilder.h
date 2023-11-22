#ifndef LAB3_STONEGOLEMBUILDER_H
#define LAB3_STONEGOLEMBUILDER_H

#include "../GolemBuilder.h"
#include "EtherealGolem.h"

template <>
class GolemBuilder<EtherealGolem> {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        EtherealGolem *type = new EtherealGolem(level);
        EtherealGolem *a = new EtherealGolem(f, coord, type, fraction);
        f.addEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_STONEGOLEMBUILDER_H
