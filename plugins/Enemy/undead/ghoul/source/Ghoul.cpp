#include "Ghoul.h"
#include "MorphismAsGhoul.tcc"
#include "NecromancyAsGhoul.tcc"

Ghoul::Ghoul(uint level, std::unique_ptr<AliveType>&& who) : UndeadType(level, std::move(who)) {}

double Ghoul::calculateCoefficient(uint level) const {
    return 0.8;
}

const std::string Ghoul::getNaming() const {
    return std::string("ghoul_") + getWhoItWas().getNaming();
}
