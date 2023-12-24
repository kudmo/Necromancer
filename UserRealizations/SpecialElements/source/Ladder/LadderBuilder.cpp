#include "Ladder/LadderBuilder.h"
#include "Ladder/Ladder.h"

#include "Dungeon/Dungeon.h"
#include "Floor/Floor.h"
#include "Field/Field.h"

const SpecialElement &LadderBuilder::build(Dungeon &dungeon, size_t floor_number, std::pair<size_t, size_t> coordinates) {
    auto &floor = dungeon.getFloorByNumber(floor_number);
    auto &field = floor.getByCoord(coordinates);
    auto ladder = new Ladder(dungeon, floor_number);
    field.setSpecialization(ladder);
    return *ladder;
}