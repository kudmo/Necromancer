#include <Wall/Wall.h>

bool Wall::isPassable() {
    return false;
}

void Wall::interact(ISmartInteractor &)  {
    //! @todo Сделать или "ударяться головой" или исключение;
}

