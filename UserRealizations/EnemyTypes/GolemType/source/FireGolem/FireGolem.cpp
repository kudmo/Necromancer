#include <FireGolem/FireGolem.h>

FireGolem::FireGolem(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<FireGolemType>&& type, FRACTIONS fraction) : Golem(f,coord, std::move(type),fraction) {}

void FireGolem::die() {
    auto magma = new Magma();
    this->getPosition().setCoverage(magma);
    Golem::die();
}