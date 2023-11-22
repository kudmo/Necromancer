#include "FireGolem.h"

FireGolem::FireGolem(Floor &f, std::pair<size_t, size_t> coord, FireGolemType *type, FRACTIONS fraction) : Golem(f, coord,type,fraction) {}

void FireGolem::die() {
    auto magma = new Magma();
    this->getPosition().setCoverage(magma);
    Golem::die();
}