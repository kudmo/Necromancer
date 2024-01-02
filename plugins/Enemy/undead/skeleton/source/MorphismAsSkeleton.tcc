#ifndef LAB3_MORPHISMASSKELETON_TCC
#define LAB3_MORPHISMASSKELETON_TCC

#include "MorphismVariations/MorphismVariation.h"
#include "Skeleton.h"

template<>
std::string MorphismAs<Skeleton>::getName() {
    return "morphism_skeleton";
}

template<>
uint MorphismAs<Skeleton>::getCost(uint level, const Object& o) {
    auto &target = dynamic_cast<const Undead&>(o);
    return (50) * std::abs(0.5 - target.getCoefficient());
}

#endif //LAB3_MORPHISMASSKELETON_TCC
