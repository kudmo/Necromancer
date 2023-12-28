#include <cstdlib>
#include <string>

#include "Ogr.h"

Ogr::Ogr(uint level): AliveType(level) {}

uint Ogr::calculateMaxHp(uint level) const {
    return start_hp + step_hp * level;
}

uint Ogr::calculateDamage(uint level) const {
    return start_damage + step_damage * level;
}

uint Ogr::calculateExperienceCount(uint level) const {
    return start_experience + step_experience * level;
}

const std::string Ogr::getNaming() const {
    return naming;
}



