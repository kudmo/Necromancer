#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "Matrix/matrix_tests.hpp"
#include "Game/enemy_tests.hpp"
#include "Game/loading_tests.hpp"
#include "Game/player_skills_test.hpp"

TEST_CASE("EnemyTests") {
    SECTION("Hunting") {
        Dungeon d = Dungeon("Test/Game/input_files/simple_test_dungeon.json");
        d.loadDungeon();
        auto &current = d.getFloorByNumber(d.getCurrentFloorNumber());
        current.loadFloor();

        auto &e1 = GlobalEnemyManager::build("alive", "goblin", d, current.getFloorNumber(), std::make_pair<size_t>(1,1), 0, FRACTIONS::ENEMY);
        auto &e2 = GlobalEnemyManager::build("undead", "skeleton_goblin", d, current.getFloorNumber(), std::make_pair<size_t>(3,1), 0, FRACTIONS::PLAYER);
        e1.hunt();
        e2.hunt();
        REQUIRE(e1.getCoordinates() == std::pair<size_t,size_t >(1,1));
        REQUIRE(e2.getCoordinates() == std::pair<size_t,size_t >(3,1));

        e1.hunt();
        REQUIRE(e1.getCoordinates() == std::pair<size_t,size_t >(2,1));

        e2.hunt();
        REQUIRE(e2.getCoordinates() == std::pair<size_t,size_t>(3,1));

        e1.hunt();
        e2.hunt();
        REQUIRE(e1.isAttacking());
        REQUIRE(e2.isAttacking());

    }
}