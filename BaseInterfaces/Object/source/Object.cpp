#include <Object/Object.h>

Floor & Object::getFloor() {
    return *floor;
}

const Floor & Object::getFloor() const {
    return *floor;
}


void Object::setFloor(Floor& floor) {
    this->floor = &floor;
}

Field & Object::getPosition() {
    return floor->getByCoord(coord);
}

const Field & Object::getPosition() const {
    return floor->getByCoord(coord);
}

std::pair<size_t, size_t> Object::getCoordinates() const {
    return coord;
}

void Object::setCoordinates(std::pair<size_t, size_t> coordinates) {
    this->coord = coordinates;
}