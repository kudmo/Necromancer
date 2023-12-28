#include "Undead/Undead.h"
#include "UndeadType/UndeadType.h"
#include "Skeleton/Skeleton.h"

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