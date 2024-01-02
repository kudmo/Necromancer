#ifndef LAB3_ETHEREALGOLEM_H
#define LAB3_ETHEREALGOLEM_H

#include <memory>

#include "Golem/Golem.h"
#include "EtherealGolemType.h"

#include "Dungeon/Dungeon.h"
#include "Field/Field.h"
#include "Floor/Floor.h"
#include "Enemy/Enemy.h"
#include "Entity/Entity.h"

class Floor;

class EtherealGolem : public Golem {
public:
    EtherealGolem(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<EtherealGolemType>&& type, FRACTIONS fraction);
    uint getEssence() const;
    const std::string getFullInfo() const override;
    void die() override;
};

template <>
class GolemBuilderAs<EtherealGolemType> : public GolemBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override {
        auto &f = dungeon.getFloorByNumber(floor);
        f.getByCoord(coord);
        auto type = std::make_unique<EtherealGolemType>(level);
        auto a = std::make_shared<EtherealGolem>(f, coord, std::move(type), fraction);
        f.summonEntity(a);
        return static_cast<Enemy&>(*a);;
    }
};
#endif //LAB3_ETHEREALGOLEM_H
