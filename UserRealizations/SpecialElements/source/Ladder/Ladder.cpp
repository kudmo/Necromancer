#include <SpecialElement/SpecialElement.h>
#include <Ladder/Ladder.h>
#include <Dungeon/Dungeon.h>
#include "Floor/Floor.h"
#include "Field/Field.h"

#include <Entity/Entity.h>

Ladder::Ladder(Dungeon &d, size_t level)  : current(level), dungeon(d) {}

bool Ladder::isPassable()  {
    return true;
}

void Ladder::interact(ISmartInteractor &e)  {
    auto &entity = dynamic_cast<Entity&>(e);
    dungeon.move(current, current + 1, entity);
}

std::string Ladder::getInfo() {
    return std::string(R"({"type" : "ladder"})");
}
