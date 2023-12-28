#ifndef LAB3_GOBLIN_H
#define LAB3_GOBLIN_H

#include <cstdlib>
#include <string>

#include "AliveType/AliveType.h"

class Goblin : public AliveType {
private:
    const uint start_hp = 10;
    const double step_hp = 2;

    const uint start_damage = 3;
    const double step_damage = 1;

    const uint start_experience = 3;
    const double step_experience = 1;

    const std::string naming = "goblin";

public:
    explicit Goblin(uint level);
    uint calculateMaxHp(uint level) const override;
    uint calculateDamage(uint level) const override;
    uint calculateExperienceCount(uint level) const override;
    const std::string getNaming() const override;
};

//extern "goblin_builder" Enemy& goblinBuilder(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
//    static AliveBuilderAs<Goblin> builder;
//    return builder.build(dungeon, floor, coord, level, fraction);
//}

#endif //LAB3_GOBLIN_H
