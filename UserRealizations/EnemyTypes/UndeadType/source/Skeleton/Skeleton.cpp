#include <Skeleton/Skeleton.h>

Skeleton::Skeleton(uint level, AliveType &who) : UndeadType(level, who) {}

double Skeleton::calculateCoefficient(uint level) const {
    return 0.5;
}

const std::string Skeleton::getNaming() const {
    return std::string("skeleton_") + getWhoItWas().getNaming();
}
