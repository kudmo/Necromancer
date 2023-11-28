#include <Entity/Entity.h>
#include <Floor/Floor.h>
#include <memory>

Entity::Entity(Floor &f, std::pair<size_t, size_t> coord, FRACTIONS fraction)
    : Object(f,coord), direction(DIRECTIONS::RIGHT), fraction(fraction) {}


void Entity::move() {
    std::pair<size_t,size_t> next_coord = getFloor().getNextByDirection(getCoordinates(), direction);
    Field& next = this->getFloor().getByCoord(next_coord);
    next.whenEntrance(*this);
    this->setCoordinates(next_coord);
}

void Entity::rotate(DIRECTIONS dir) {
    direction = dir;
}

void Entity::stay()  {
    getPosition().whenStay(*this);
}

 DIRECTIONS Entity::getDirection() const {
    return direction;
}

 FRACTIONS Entity::getFraction() const {
    return fraction;
}

void Entity::attack(IAttackable &target) {
    target.damaged(*this, getDamage());
}

void Entity::die() {
    getFloor().removeEntity(*this);
}

