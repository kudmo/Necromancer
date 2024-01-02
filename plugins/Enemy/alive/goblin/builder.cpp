#include "Alive/Alive.h"
#include "AliveType/AliveType.h"
#include "source/Goblin.h"

extern "C" std::string getName() {
    return "goblin";
}

extern "C" AliveBuilder& getBuilder() {
    static AliveBuilderAs<Goblin> builder;
    return builder;
}

extern "C" AliveTypeBuilder& getTypeBuilder() {
    static AliveTypeBuilderAs<Goblin> builder;
    return builder;
}