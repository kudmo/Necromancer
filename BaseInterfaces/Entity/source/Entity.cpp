#include <Entity/Entity.h>
#include <Floor/Floor.h>
#include <memory>
#include <Exceptions/EntityExceptions.h>
#include <iostream>

Entity::Entity(Floor &f, std::pair<size_t, size_t> coord, FRACTIONS fraction)
    : Object(f,coord), direction(DIRECTIONS::RIGHT), fraction(fraction) {}


void Entity::move() {
    if(isDead())
        throw entity_errors::already_dead_exception("Dead can't");
    std::pair<size_t,size_t> next_coord = getFloor().getNextByDirection(getCoordinates(), direction);
    Field& next = this->getFloor().getByCoord(next_coord);
    getPosition().whenOut(*this);
    next.whenEntrance(*this);
    this->setCoordinates(next_coord);
}

void Entity::rotate(DIRECTIONS dir) {
    if(isDead())
        throw entity_errors::already_dead_exception("Dead can't");
    direction = dir;
}

void Entity::stay()  {
    if(isDead())
        throw entity_errors::already_dead_exception("Dead can't");
    try {
        getPosition().whenStay(*this);
    } catch (dungeon_errors::invalid_position_error&) {
        this->die();
    }
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

