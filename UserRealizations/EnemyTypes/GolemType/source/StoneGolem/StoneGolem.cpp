#include <StoneGolem/StoneGolem.h>

StoneGolem::StoneGolem(Floor &f, std::pair<size_t, size_t> coord, StoneGolemType *type, FRACTIONS fraction): Golem(f,coord, type,fraction) {}

void StoneGolem::die() {
    auto wall = new Wall();
    this->getPosition().setSpecialization(wall);
    Golem::die();
}
