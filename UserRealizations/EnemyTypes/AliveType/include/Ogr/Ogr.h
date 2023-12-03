#ifndef LAB3_OGR_H
#define LAB3_OGR_H

#include <cstdlib>
#include <string>

#include <AliveType/AliveType.h>

class Ogr : public AliveType {
private:
    const uint start_hp = 15;
    const double step_hp = 3;

    const uint start_damage = 5;
    const double step_damage = 2;

    const uint start_experience = 10;
    const double step_experience = 1.5;

    const std::string naming = "ogr";
public:
    Ogr(uint level);
    uint calculateMaxHp(uint level) const override;
    uint calculateDamage(uint level) const override;
    uint calculateExperienceCount(uint level) const override;
    const std::string getNaming() const override;
};

#endif //LAB3_OGR_H
