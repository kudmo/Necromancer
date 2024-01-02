#ifndef LAB3_NECROMANCYASGHOUL_TCC
#define LAB3_NECROMANCYASGHOUL_TCC

#include "NecromancyVariations/NecromancyVariation.h"
#include "Fantomas.h"

template<>
std::string NecromancyAs<Fantomas>::getName() {
    return "necromancy_fantomas";
}

#endif //LAB3_NECROMANCYASGHOUL_TCC
