#include "Undead/Undead.h"
#include "UndeadType/UndeadType.h"
#include "MorphismVariations/MorphismVariation.h"
#include "NecromancyVariations/NecromancyVariation.h"

#include "source/Skeleton.h"

extern "C" std::string getName() {return "skeleton";}
extern "C" double getCoefficient() {return 0.5;}

extern "C" UndeadBuilder& getBuilder() {
    static UndeadBuilderAs<Skeleton> builder;
    return builder;
}

extern "C" UndeadTypeBuilder& getTypeBuilder() {
    static UndeadTypeBuilderAs<Skeleton> builder;
    return builder;
}

extern "C" MorphismVariationBuilder& getMorphismBuilder() {
    static MorphismAsBuilder<Skeleton> builder;
    return builder;
}


extern "C" NecromancyVariationBuilder& getNecromancyBuilder() {
    static NecromancyAsBuilder<Skeleton> builder;
    return builder;
}
