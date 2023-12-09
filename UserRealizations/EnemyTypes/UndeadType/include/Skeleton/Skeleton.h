#ifndef LAB3_SKELETON_H
#define LAB3_SKELETON_H


#include <cstdlib>
#include "UndeadType/UndeadType.h"
#include "AliveType/AliveType.h"
#include <NecromancyVariations/NecromancyVariation.h>

class Skeleton : public UndeadType {
public:
    Skeleton(uint level, std::unique_ptr<AliveType>&& who);
    double calculateCoefficient(uint level) const override;
    const std::string getNaming() const override;
};

#endif //LAB3_SKELETON_H
