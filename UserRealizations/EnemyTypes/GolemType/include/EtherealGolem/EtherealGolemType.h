#ifndef LAB3_ETHEREALGOLEMTYPE_H
#define LAB3_ETHEREALGOLEMTYPE_H

#include <cstdlib>
#include <string>

#include <GolemType/GolemType.h>

class EtherealGolemType : public GolemType {
private:
    const uint start_hp = 15;
    const double step_hp = 3;

    const uint start_damage = 5;
    const double step_damage = 2;

    const uint start_experience = 10;
    const double step_experience = 1.5;

    const uint start_probability = 10;
    const double step_probability = 1.5;

    const uint start_essence = 20;
    const double step_essence = 5;

    const std::string naming = "EtherealGolem";
public:
    EtherealGolemType(uint level) : GolemType(level) {}

    uint calculateMaxHp(uint level) const override;
    uint calculateDamage(uint level) const override;
    uint calculateExperienceCount(uint level) const override;
    uint calculateIgnoringProbability(uint level) const override;

    uint calculateEssenceCount(uint level) const;
    uint getEssenceCount() const;

    const std::string getNaming() const override;
};
#endif //LAB3_ETHEREALGOLEMTYPE_H
