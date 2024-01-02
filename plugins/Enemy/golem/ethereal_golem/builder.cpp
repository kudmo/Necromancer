#include "Golem/Golem.h"
#include "GolemType/GolemType.h"
#include "source/EtherealGolem.h"

extern "C" std::string getName() {return "ethereal_golem";}

extern "C" GolemBuilder& getBuilder() {
    static GolemBuilderAs<EtherealGolemType> builder;
    return builder;
}

extern "C" GolemTypeBuilder& getTypeBuilder() {
    static GolemTypeBuilderAs<EtherealGolemType> builder;
    return builder;
}