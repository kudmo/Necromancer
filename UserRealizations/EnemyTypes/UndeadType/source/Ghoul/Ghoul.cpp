#include <Ghoul/Ghoul.h>

Ghoul::Ghoul(uint level, AliveType &who) : UndeadType(level, who) {}

double Ghoul::calculateCoefficient(uint level) const {
    return 0.8;
}

const std::string Ghoul::getNaming() const {
    return std::string("Ghoul - ") + getWhoItWas().getNaming();
}
