#include "Magma/MagmaBuilder.h"
#include "Magma/Magma.h"
#include "Dungeon/Dungeon.h"
#include "Floor/Floor.h"
#include "Field/Field.h"

const Coverage &MagmaBuilder::build(Dungeon &dungeon, size_t floor_number, std::pair<size_t, size_t> coordinates) {
    auto &floor = dungeon.floorByNumber(floor_number);
    auto &field = floor.getByCoord(coordinates);
    auto magma = new Magma();
    field.setCoverage(magma);
    return *magma;
}
