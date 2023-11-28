#include <FireGolem/FireGolem.h>


void FireGolem::die() {
    auto magma = new Magma();
    this->getPosition().setCoverage(magma);
    Golem::die();
}