#ifndef LAB3_ETHEREALGOLEM_H
#define LAB3_ETHEREALGOLEM_H


#include <Golem/Golem.h>
#include <EtherealGolem/EtherealGolemType.h>

#include <Floor/Floor.h>
#include <Enemy/Enemy.h>
#include <Entity/Entity.h>

class Floor;

class EtherealGolem : public Golem {
public:
    //!@todo Конструктор??
    EtherealGolem(Floor& f, std::pair<size_t,size_t> coord, EtherealGolemType* type, FRACTIONS fraction);
    uint getEssence() const;
    void die() override;
};

template <>
class GolemBuilder<EtherealGolemType> {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        EtherealGolemType *type = new EtherealGolemType(level);
        EtherealGolem *a = new EtherealGolem(f, coord, type, fraction);
        f.summonEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_ETHEREALGOLEM_H
