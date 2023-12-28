#include "Alive/Alive.h"
#include "AliveType/AliveType.h"
#include "Ogr/Ogr.h"
extern "C" std::string getName() {return "ogr";}

extern "C" AliveBuilder& getBuilder() {
    static AliveBuilderAs<Ogr> builder;
    return builder;
}

extern "C" AliveTypeBuilder& getTypeBuilder() {
    static AliveTypeBuilderAs<Ogr> builder;
    return builder;
}