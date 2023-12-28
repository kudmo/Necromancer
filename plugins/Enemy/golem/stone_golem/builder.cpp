#include "Golem/Golem.h"
#include "GolemType/GolemType.h"
#include "StoneGolem/StoneGolem.h"

extern "C" std::string getName() {return "stone_golem";}

extern "C" GolemBuilder& getBuilder() {
    static GolemBuilderAs<StoneGolemType> builder;
    return builder;
}

extern "C" GolemTypeBuilder& getTypeBuilder() {
    static GolemTypeBuilderAs<StoneGolemType> builder;
    return builder;
}