#ifndef LAB3_FIREGOLEMTYPE_H
#define LAB3_FIREGOLEMTYPE_H

#include <utility>
#include <string>
#include "../GolemType.h"

class FireGolemType : public GolemType {
private:
    const uint start_hp = 15;
    const double step_hp = 3;

    const uint start_damage = 5;
    const double step_damage = 2;

    const uint start_experience = 10;
    const double step_experience = 1.5;

    const uint start_probability = 10;
    const double step_probability = 1.5;

    const std::string naming = "FireGolem";
public:
    uint calculateMaxHp(uint level) const override { return start_hp + step_hp * level;};
    uint calculateDamage(uint level) const override { return start_damage + step_damage * level;};
    uint calculateExperienceCount(uint level) const override { return start_experience + step_experience * level;};
    uint calculateIgnoringProbability(uint level) const override { return start_probability + start_experience * level;};
    const std::string getNaming() const override {return naming;}
};

#endif //LAB3_FIREGOLEMTYPE_H
