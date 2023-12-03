#include <catch2/catch.hpp>
#include <Dungeon/Dungeon.h>
#include <Floor/Floor.h>

TEST_CASE("DungeonLoading") {
    SECTION("Simple") {
        Dungeon d = Dungeon("Test/input_files/test_dungeon.json");
        d.loadDungeon();
        auto &f = d.floorByNumber(0);
        f.loadFloor();
        f.print();
    }
}