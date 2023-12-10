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
    Golem(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<GolemType>&& type, FRACTIONS fraction);

    uint getIgnoringProbability() const;
    void damaged(IAttacker &attacker, uint damage) override;
    const std::string getFullInfo() const override;
    const std::string getTypeName() const override {return "golem";}
    void die() override;
};

class GolemBuilder {
public:
    virtual Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const = 0;
    virtual ~GolemBuilder() = default;
};

template <class T> requires std::is_base_of_v<GolemType, T>
class GolemBuilderAs : public GolemBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override;
};
#endif //LAB3_GOLEM_H
