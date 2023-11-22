#include "EtherealGolem.h"

EtherealGolem::EtherealGolem(Floor &f, std::pair<size_t, size_t> coord, EtherealGolemType *type, FRACTIONS fraction) : Golem(f, coord,type,fraction) {}

uint EtherealGolem::getEssence() const {
    auto t = static_cast<EtherealGolemType*>(type);
    return t->getEssenceCount();
}

void EtherealGolem::die() {
    this->getPosition().addEssence(this->getEssence());
    Golem::die();
}