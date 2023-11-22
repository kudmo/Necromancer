#ifndef LAB3_STONEGOLEMBUILDER_H
#define LAB3_STONEGOLEMBUILDER_H

#include "../GolemBuilder.h"
#include "StoneGolem.h"

template <>
class GolemBuilder<StoneGolem> {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        StoneGolem *type = new StoneGolem(level);
        StoneGolem *a = new StoneGolem(f, coord, type, fraction);
        f.addEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_STONEGOLEMBUILDER_H
