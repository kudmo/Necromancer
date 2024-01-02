#ifndef LAB3_MORPHISMASGHOUL_TCC
#define LAB3_MORPHISMASGHOUL_TCC

#include "MorphismVariations/MorphismVariation.h"
#include "Fantomas.h"

template<>
std::string MorphismAs<Fantomas>::getName() {
    return "morphism_fantomas";
}

template<>
uint MorphismAs<Fantomas>::getCost(uint level, const Object& o) {
    auto &target = dynamic_cast<const Undead&>(o);
    return (50)*std::abs(1.2 - target.getCoefficient());
}

#endif //LAB3_MORPHISMASGHOUL_TCC
