#include "Wall/WallBuilder.h"
#include "Wall/Wall.h"

#include "Dungeon/Dungeon.h"
#include "Floor/Floor.h"
#include "Field/Field.h"

const SpecialElement &WallBuilder::build(Dungeon &dungeon, size_t floor_number, std::pair<size_t, size_t> coordinates) {
    auto &floor = dungeon.getFloorByNumber(floor_number);
    auto &field = floor.getByCoord(coordinates);
    auto door = new Wall();
    field.setSpecialization(door);
    return *door;
}