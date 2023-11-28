#include <FireGolem/FireGolemType.h>


FireGolemType::FireGolemType(uint level) : GolemType(level) {

}

uint FireGolemType::calculateMaxHp(uint level) const {
    return start_hp + step_hp * level;
}

uint FireGolemType::calculateDamage(uint level) const {
    return start_damage + step_damage * level;
}

uint FireGolemType::calculateExperienceCount(uint level) const {
     return start_experience + step_experience * level;
}

uint FireGolemType::calculateIgnoringProbability(uint level) const {
    return start_probability + step_probability * level;
}

const std::string FireGolemType::getNaming() const {
    return naming;
}

