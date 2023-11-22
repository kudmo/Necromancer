#include "Ladder.h"

Ladder::Ladder(Dungeon &d, size_t from, size_t to)  : from(from), to(to), dungeon(d) {}

bool Ladder::isPassable()  {
    return true;
}

void Ladder::interact(ISmartInteractor &e)  {
    Entity &entity = dynamic_cast<Entity&>(e);
    dungeon.move(from, to, entity);
}