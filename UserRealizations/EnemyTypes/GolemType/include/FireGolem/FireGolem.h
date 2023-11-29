#ifndef LAB3_FIREGOLEM_H
#define LAB3_FIREGOLEM_H

#include <Golem/Golem.h>

#include "Coverage/Coverage.h"
#include "Magma/Magma.h"
#include <FireGolem/FireGolemType.h>
#include <Dungeon/Dungeon.h>

class FireGolem : public Golem {
public:
    FireGolem(Floor& f, std::pair<size_t,size_t> coord, FireGolemType* type, FRACTIONS fraction);
    void die() override;
};

template <>
class GolemBuilderAs<FireGolemType> : public GolemBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override {
        auto &f = dungeon.floorByNumber(floor);
        f.getByCoord(coord);
        auto *type = new FireGolemType(level);
        auto *a = new FireGolem(f, coord, type, fraction);
        f.summonEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};

#endif //LAB3_FIREGOLEM_H
