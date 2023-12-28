#include "EtherealGolemType.h"

uint EtherealGolemType::calculateMaxHp(uint level) const {
    return start_hp + step_hp * level;
}

uint EtherealGolemType::calculateDamage(uint level) const {
    return start_damage + step_damage * level;
}

uint EtherealGolemType::calculateExperienceCount(uint level) const {
     return start_experience + step_experience * level;
}

uint EtherealGolemType::calculateIgnoringProbability(uint level) const {
    return start_probability + step_probability * level;
}

uint EtherealGolemType::calculateEssenceCount(uint level) const {
    return start_essence + step_essence * level;
}

uint EtherealGolemType::getEssenceCount() const {
    return calculateEssenceCount(getLevel());
}

const std::string EtherealGolemType::getNaming() const {
    return naming;
}