#ifndef LAB3_MORPHISMASGHOUL_TCC
#define LAB3_MORPHISMASGHOUL_TCC

#include "MorphismVariations/MorphismVariation.h"
#include "Ghoul.h"

template<>
std::string MorphismAs<Ghoul>::getName() {
    return "morphism_ghoul";
}

template<>
uint MorphismAs<Ghoul>::getCost(uint level, const Object& o) {
    auto &target = dynamic_cast<const Undead&>(o);
    return (50)*std::abs(0.8 - target.getCoefficient());
}

#endif //LAB3_MORPHISMASGHOUL_TCC
