#include "Golem/Golem.h"
#include "GolemType/GolemType.h"
#include "FireGolem/FireGolem.h"

extern "C" std::string getName() {return "fire_golem";}

extern "C" GolemBuilder& getBuilder() {
    static GolemBuilderAs<FireGolemType> builder;
    return builder;
}

extern "C" GolemTypeBuilder& getTypeBuilder() {
    static GolemTypeBuilderAs<FireGolemType> builder;
    return builder;
}