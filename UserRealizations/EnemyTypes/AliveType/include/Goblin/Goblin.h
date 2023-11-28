#ifndef LAB3_GOBLIN_H
#define LAB3_GOBLIN_H

#include <cstdlib>
#include <string>

#include <AliveType/AliveType.h>

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
    Goblin(uint level);
    uint calculateMaxHp(uint level) const override;
    uint calculateDamage(uint level) const override;
    uint calculateExperienceCount(uint level) const override;
    const std::string getNaming() const override;
};
#endif //LAB3_GOBLIN_H
