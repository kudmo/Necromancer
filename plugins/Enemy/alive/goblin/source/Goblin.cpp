#include "Goblin.h"

Goblin::Goblin(uint level): AliveType(level) {}

uint Goblin::calculateMaxHp(uint level) const {
    return start_hp + step_hp * level;
}

uint Goblin::calculateDamage(uint level) const {
    return start_damage + step_damage * level;
}

uint Goblin::calculateExperienceCount(uint level) const {
    return start_experience + step_experience * level;
}

const std::string Goblin::getNaming() const {
    return naming;
}





