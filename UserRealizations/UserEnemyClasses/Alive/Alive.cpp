#include "Alive.h"

Alive::Alive(Floor &f, std::pair<size_t, size_t> coord, AliveType *type, FRACTIONS fraction) : Enemy(f, coord, type, fraction) {}

void Alive::die()  {
    Field& position = this->getPosition();
    auto body = new DeadBody(getFloor(), getCoordinates(), dynamic_cast<AliveType*>(this->type));
    position.addItem(*body);
    Enemy::die();
}