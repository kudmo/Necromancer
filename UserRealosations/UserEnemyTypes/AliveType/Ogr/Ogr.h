#ifndef LAB3_OGR_H
#define LAB3_OGR_H

#include <utility>

#include "../AliveType.h"

class Ogr : public AliveType {
private:
    const uint start_hp = 15;
    const double step_hp = 3;

    const uint start_damage = 5;
    const double step_damage = 2;

    const uint start_experience = 10;
    const double step_experience = 1.5;

    const std::string naming = "Ogr";
public:
    Ogr(uint level): AliveType(level) {;};
    uint calculateMaxHp(uint level) const override { return start_hp + step_hp * level;};
    uint calculateDamage(uint level) const override { return start_damage + step_damage * level;};
    uint calculateExperienceCount(uint level) const override { return start_experience + step_damage * level;};
    const std::string getNaming() const override  {return namin;};
};

#endif //LAB3_OGR_H
