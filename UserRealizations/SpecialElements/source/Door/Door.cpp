#include <Door/Door.h>

bool Door::isPassable() {
    return opened;
}

void Door::interact(ISmartInteractor &e) {
    opened = !opened;
}

SpecialElement *DoorBuilder::build() {
    return new Door();
}