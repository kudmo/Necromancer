#ifndef LAB3_ETHEREALGOLEM_H
#define LAB3_ETHEREALGOLEM_H


#include <Golem/Golem.h>
#include <EtherealGolem/EtherealGolemType.h>

#include <Dungeon/Dungeon.h>
#include <Floor/Floor.h>
#include <Enemy/Enemy.h>
#include <Entity/Entity.h>

class Floor;

class EtherealGolem : public Golem {
public:
    EtherealGolem(Floor& f, std::pair<size_t,size_t> coord, EtherealGolemType* type, FRACTIONS fraction);
    uint getEssence() const;
    const std::string getFullInfo() const override;
    void die() override;
};

template <>
class GolemBuilderAs<EtherealGolemType> : public GolemBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override {
        auto &f = dungeon.floorByNumber(floor);
        f.getByCoord(coord);
        auto *type = new EtherealGolemType(level);
        auto *a = new EtherealGolem(f, coord, type, fraction);
        f.summonEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_ETHEREALGOLEM_H
