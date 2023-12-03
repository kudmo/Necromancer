#include <Door/Door.h>

bool Door::isPassable() {
    return opened;
}

void Door::interact(ISmartInteractor &e) {
    opened = !opened;
}

std::string Door::getInfo() {
    return std::string(R"({"type" : "door"})");
}


