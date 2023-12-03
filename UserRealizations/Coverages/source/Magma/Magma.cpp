#include "Magma/Magma.h"

bool Magma::isPassable() {return true;}

void Magma::effect(Entity &e) {
    e.damaged(*this, damage);
}

std::string Magma::getInfo() const {
    return std::string(R"({"type" : "magma"})");
}
