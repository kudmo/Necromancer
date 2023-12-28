#ifndef LAB3_NECROMANCYASSKELETON_TCC
#define LAB3_NECROMANCYASSKELETON_TCC

#include "NecromancyVariations/NecromancyVariation.h"
#include "Skeleton/Skeleton.h"

template<>
std::string NecromancyAs<Skeleton>::getName() {
    return "necromancy_skeleton";
}

#endif //LAB3_NECROMANCYASSKELETON_TCC
