#include <catch2/catch.hpp>
#include <memory>
#include <jsoncpp/json/json.h>

#include <Dungeon/Dungeon.h>
#include <Floor/Floor.h>
#include <Player/Player.h>

#include <GlobalSkillManager.h>
#include <GlobalEnemyManager.h>
#include "DeadBody/DeadBody.h"

TEST_CASE("PlayerSkills") {
    SECTION("CreatingDefaultSkillTable") {
        Dungeon d = Dungeon("Test/Game/input_files/simple_test_dungeon.json");
        d.loadDungeon();
        auto &current = d.getFloorByNumber(d.getCurrentFloorNumber());
        current.loadFloor();
        std::unique_ptr<SkillTable> table;
        std::vector<std::string>  _table {"curse", "desiccation","necromancy", "morphism"};
        REQUIRE_NOTHROW(table = GlobalSkillManager::buildSkillTableDefault(_table));

        auto p = std::make_shared<Player>(current, std::make_pair<size_t>(1,1), std::move(table));
        current.addEntity(p);

        auto p_info = p->getFullInfo();
        Json::Value json_info;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(p_info, json_info );
        REQUIRE(parsingSuccessful);
        Json::Value var;
        REQUIRE_NOTHROW(var = json_info["skills_info"]);
        REQUIRE(var["skill_count"].asInt() == 4);
        for (int i = 0; i < 4; ++i) {
            auto &curr = var["skills"][i];
            if (curr["main_name"].asString() == "curse") {
                REQUIRE(curr["variations"].size() == 1);
                REQUIRE(curr["variations"][0].asString() == "curse_curse");
            } else if(curr["main_name"].asString() == "desiccation") {
                REQUIRE(curr["variations"].size() == 2);
                REQUIRE(curr["variations"][0].asString() == "desiccation_health");
                REQUIRE(curr["variations"][1].asString() == "desiccation_mana");
            } else if(curr["main_name"].asString() == "necromancy") {
                REQUIRE(curr["variations"].size() == 1);
                REQUIRE(curr["variations"][0].asString() == "necromancy_skeleton");
            }  else if(curr["main_name"].asString() == "morphism") {
                REQUIRE(curr["variations"].size() == 1);
                REQUIRE(curr["variations"][0].asString() == "morphism_skeleton");
            } else {
                REQUIRE(1 == 2);
            }
        }
    }
    SECTION("ExploringNewUndead") {
        Dungeon d = Dungeon("Test/Game/input_files/simple_test_dungeon.json");
        d.loadDungeon();
        auto &current = d.getFloorByNumber(d.getCurrentFloorNumber());
        current.loadFloor();

        std::unique_ptr<SkillTable> table;
        std::vector<std::string>  _table {"curse", "desiccation", "necromancy", "morphism"};
        REQUIRE_NOTHROW(table = GlobalSkillManager::buildSkillTableDefault(_table));

        auto p = std::make_shared<Player>(current, std::make_pair<size_t>(1,1), std::move(table));
        current.addEntity(p);
        auto known = p->getAllExploredUndeadTypes();
        REQUIRE(known.size() == 1);
        REQUIRE(known[0] == "skeleton");
        REQUIRE_THROWS_AS(p->exploreNewUndeadType("skeleton"), player_errors::player_exception);
        REQUIRE_THROWS_AS(p->exploreNewUndeadType("ghoul"), player_errors::invalid_upgrade_error);
        p->collectEssence(100);
        REQUIRE_NOTHROW(p->exploreNewUndeadType("ghoul"));

        GlobalEnemyManager::getInstance().build("alive", "goblin", d, current.getFloorNumber(), std::make_pair<size_t>(2,2), 0);
        std::shared_ptr<Entity> goblin;
        auto entinies = current.getEntities();
        for (auto &i : entinies) {
            auto e = i.lock();
            if (e && !e->isDead() && e->getNaming() == "goblin") {
                goblin = e;
            }
        }
        REQUIRE_NOTHROW(p->useSkill("curse", "curse_curse", *goblin));
        auto &items = d.getFloorByNumber(0).getByCoord(2, 2).getItems();
        REQUIRE(items.size() == 1);
        REQUIRE_NOTHROW(dynamic_cast<DeadBody&>(items[0].get()));
        auto &body = dynamic_cast<DeadBody&>(items[0].get());
        REQUIRE_NOTHROW(p->useSkill("necromancy", "necromancy_ghoul", body));

    }
}