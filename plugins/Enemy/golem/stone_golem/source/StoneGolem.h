#ifndef LAB3_STONEGOLEM_H
#define LAB3_STONEGOLEM_H

#include "Golem/Golem.h"
#include <StoneGolem/StoneGolemType.h>

#include "SpecialElement/SpecialElement.h"
#include "Wall/Wall.h"
#include "Floor/Floor.h"
#include "Dungeon/Dungeon.h"
#include "Enemy/Enemy.h"
#include "Entity/Entity.h"


class StoneGolem : public Golem {
public:
    StoneGolem(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<StoneGolemType>&& type, FRACTIONS fraction);
    void die() override;
};

template <>
class GolemBuilderAs<StoneGolemType> : public GolemBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override {
        auto &f = dungeon.getFloorByNumber(floor);
        f.getByCoord(coord);
        auto type = std::make_unique<StoneGolemType>(level);
        auto a = std::make_shared<StoneGolem>(f, coord, std::move(type), fraction);
        f.summonEntity(a);
        return static_cast<Enemy&>(*a);
    }
};

#endif //LAB3_STONEGOLEM_H
