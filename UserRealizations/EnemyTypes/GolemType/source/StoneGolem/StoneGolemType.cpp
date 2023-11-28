#include <StoneGolem/StoneGolemType.h>

StoneGolemType::StoneGolemType(uint level) : GolemType(level) {}

uint StoneGolemType::calculateMaxHp(uint level) const {
    return start_hp + step_hp * level;
}

uint StoneGolemType::calculateDamage(uint level) const {
    return start_damage + step_damage * level;
}

uint StoneGolemType::calculateExperienceCount(uint level) const {
     return start_experience + step_experience * level;
}

uint StoneGolemType::calculateIgnoringProbability(uint level) const {
    return start_probability + step_probability * level;
}

const std::string StoneGolemType::getNaming() const {
    return naming;
}

