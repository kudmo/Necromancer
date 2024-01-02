#include "Undead/Undead.h"
#include "UndeadType/UndeadType.h"
#include "MorphismVariations/MorphismVariation.h"
#include "NecromancyVariations/NecromancyVariation.h"

#include "source/Fantomas.h"

extern "C" std::string getName() {return "fantomas";}
extern "C" double getCoefficient() {return 1.2;}

extern "C" UndeadBuilder& getBuilder() {
    static UndeadBuilderAs<Fantomas> builder;
    return builder;
}

extern "C" UndeadTypeBuilder& getTypeBuilder() {
    static UndeadTypeBuilderAs<Fantomas> builder;
    return builder;
}

extern "C" MorphismVariationBuilder& getMorphismBuilder() {
    static MorphismAsBuilder<Fantomas> builder;
    return builder;
}

extern "C" NecromancyVariationBuilder& getNecromancyBuilder() {
    static NecromancyAsBuilder<Fantomas> builder;
    return builder;
}