#include "UndeadType/UndeadType.h"
#include "Exceptions/EnemyExceptions.h"
#include <memory>
UndeadType::UndeadType(uint level, std::unique_ptr<AliveType>&& who) : EnemyType(level) {
    who_it_was = std::move(who);
    if (!who_it_was)
        throw enemy_errors::invalid_type_error("type must be not nullptr");
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

std::unique_ptr<AliveType> UndeadType::takeInnerBody() {
    std::unique_ptr<AliveType> dead_type;
    dead_type.reset(dynamic_cast<AliveType *>(who_it_was.release()));
    return dead_type;
}
