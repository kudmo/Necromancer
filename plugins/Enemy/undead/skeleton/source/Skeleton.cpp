#include "Skeleton.h"
#include "NecromancyAsSkeleton.tcc"
#include "MorphismAsSkeleton.tcc"

Skeleton::Skeleton(uint level, std::unique_ptr<AliveType>&& who) : UndeadType(level, std::move(who)) {}

double Skeleton::calculateCoefficient(uint level) const {
    return 0.5;
}

const std::string Skeleton::getNaming() const {
    return std::string("skeleton_") + getWhoItWas().getNaming();
}
