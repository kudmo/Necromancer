#include "Undead/Undead.h"
#include "UndeadType/UndeadType.h"
#include "Ghoul/Ghoul.h"

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