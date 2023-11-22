#include "UndeadType.h"

UndeadType::UndeadType(uint level, AliveType &who) : EnemyType(level) {
    who_it_was = &who;
}

const AliveType &UndeadType::getWhoItWas() const {
    return *who_it_was;
};

uint UndeadType::getCoefficient() {
    return calculateCoefficient(getLevel());
}