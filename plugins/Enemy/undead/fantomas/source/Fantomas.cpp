#include "Fantomas.h"
#include "MorphismAsFantomas.tcc"
#include "NecromancyAsFantomas.tcc"

Fantomas::Fantomas(uint level, std::unique_ptr<AliveType>&& who) : UndeadType(level, std::move(who)) {}

double Fantomas::calculateCoefficient(uint level) const {
    return 1.2;
}

const std::string Fantomas::getNaming() const {
    return std::string("fantomas_") + getWhoItWas().getNaming();
}
