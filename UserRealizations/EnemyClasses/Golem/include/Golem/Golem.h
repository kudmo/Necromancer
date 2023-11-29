#ifndef LAB3_GOLEM_H
#define LAB3_GOLEM_H

#include <cstdlib>
#include <ctime>
#include <random>

#include <Enemy/Enemy.h>
#include <GolemType/GolemType.h>
#include <IAttacker.h>
#include <Entity/Entity.h>

class Floor;

class Golem : public Enemy {
public:
    Golem(Floor& f, std::pair<size_t,size_t> coord, GolemType* type, FRACTIONS fraction);

    //!@todo дописать игнор урона
    uint getIgnoringProbability() const {return dynamic_cast<GolemType*>(type)->getIgnoringProbability();};
    uint damaged(IAttacker &attacker, uint damage) override;

    void die() override;
};

class GolemBuilder {
public:
    virtual Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const = 0;

};

template <class T> requires std::is_base_of_v<GolemType, T>
class GolemBuilderAs : public GolemBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override;
};
#endif //LAB3_GOLEM_H
