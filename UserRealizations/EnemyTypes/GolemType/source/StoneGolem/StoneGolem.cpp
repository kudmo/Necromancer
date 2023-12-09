#include <StoneGolem/StoneGolem.h>

StoneGolem::StoneGolem(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<StoneGolemType>&& type, FRACTIONS fraction): Golem(f,coord, std::move(type), fraction) {}

void StoneGolem::die() {
    auto wall = new Wall();
    this->getPosition().setSpecialization(wall);
    Golem::die();
}
