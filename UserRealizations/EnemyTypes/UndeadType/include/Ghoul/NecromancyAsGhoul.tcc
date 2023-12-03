#ifndef LAB3_NECROMANCYASGHOUL_TCC
#define LAB3_NECROMANCYASGHOUL_TCC

#include <NecromancyVariations/NecromancyVariation.h>
#include "Ghoul/Ghoul.h"

template<>
std::string NecromancyAs<Ghoul>::getName() {
    return "necromancy_ghoul";
}

#endif //LAB3_NECROMANCYASGHOUL_TCC
