#include <Wall/Wall.h>
#include "Dungeon/Dungeon.h"
#include "Floor/Floor.h"
#include "Field/Field.h"

bool Wall::isPassable() {
    return false;
}

void Wall::interact(ISmartInteractor &)  {
    //! @todo Сделать или "ударяться головой" или исключение;
}

std::string Wall::getInfo() {
    return std::string(R"({"type" : "wall"})");

}

