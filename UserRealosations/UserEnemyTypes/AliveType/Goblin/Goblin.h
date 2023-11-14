#ifndef LAB3_GOBLIN_H
#define LAB3_GOBLIN_H

#include <utility>

#include "../AliveType.h"

class Goblin : public AliveType {
private:
    const uint start_hp = 10;
    const double step_hp = 2;

    const uint start_damage = 3;
    const double step_damage = 1;

    const uint start_experience = 3;
    const double step_experience = 1;

    const std::string naming = "Goblin";

public:
    Goblin(uint level): AliveType(level) {};
    uint calculateMaxHp(uint level) const override { return start_hp + step_hp * level;};
    uint calculateDamage(uint level) const override { return start_damage + step_damage * level;};
    uint calculateExperienceCount(uint level) const override { return start_experience + step_damage * level;};
    const std::string getNaming() const override {return naming};
};
#endif //LAB3_GOBLIN_H
