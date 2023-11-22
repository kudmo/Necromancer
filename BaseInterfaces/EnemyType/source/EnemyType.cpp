#include <EnemyType/EnemyType.h>

EnemyType::EnemyType(uint level): level(level) {}

uint EnemyType::getLevel() const {
    return level;
}

uint EnemyType::getMaxHp() const {
    return calculateMaxHp(level);
}

uint EnemyType::getDamage() const {
    return calculateDamage(level);
}

uint EnemyType::getExperienceCount() const {
    return calculateExperienceCount(level);
}