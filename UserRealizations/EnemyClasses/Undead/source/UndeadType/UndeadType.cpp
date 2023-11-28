#include "../../include/UndeadType/UndeadType.h"

UndeadType::UndeadType(uint level, AliveType &who) : EnemyType(level) {
    who_it_was = &who;
}

const AliveType &UndeadType::getWhoItWas() const {
    return *who_it_was;
};

double UndeadType::getCoefficient() const{
    return calculateCoefficient(getLevel());
}

uint UndeadType::calculateMaxHp(uint level) const {
    return static_cast<uint>(getCoefficient() * who_it_was->calculateMaxHp(level));
}

uint UndeadType::calculateDamage(uint level) const {
    return static_cast<uint>(getCoefficient() * who_it_was->calculateDamage(level));
}

uint UndeadType::calculateExperienceCount(uint level) const {
    return static_cast<uint>(getCoefficient() * who_it_was->calculateExperienceCount(level));
}

UndeadType::~UndeadType() {
    delete who_it_was;
}
