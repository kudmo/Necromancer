#include "Undead/Undead.h"
#include "UndeadType/UndeadType.h"
#include "MorphismVariations/MorphismVariation.h"
#include "NecromancyVariations/NecromancyVariation.h"

#include "source/Ghoul.h"

extern "C" std::string getName() {return "ghoul";}
extern "C" double getCoefficient() {return 0.8;}

extern "C" UndeadBuilder& getBuilder() {
    static UndeadBuilderAs<Ghoul> builder;
    return builder;
}

extern "C" UndeadTypeBuilder& getTypeBuilder() {
    static UndeadTypeBuilderAs<Ghoul> builder;
    return builder;
}

extern "C" MorphismVariationBuilder& getMorphismBuilder() {
    static MorphismAsBuilder<Ghoul> builder;
    return builder;
}

extern "C" NecromancyVariationBuilder& getNecromancyBuilder() {
    static NecromancyAsBuilder<Ghoul> builder;
    return builder;
}