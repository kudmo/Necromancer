#include <GlobalEnemyManager.h>
#include <functional>

#include "Dungeon/Dungeon.h"

#include <Alive/Alive.h>
#include "Goblin/Goblin.h"
#include "Ogr/Ogr.h"

#include "Undead/Undead.h"
#include "Skeleton/Skeleton.h"
#include "Ghoul/Ghoul.h"

#include "Golem/Golem.h"
#include "StoneGolem/StoneGolem.h"
#include "FireGolem/FireGolem.h"
#include "EtherealGolem/EtherealGolem.h"


Enemy & GlobalEnemyManager::build(const std::string &enemy_class,
                                  const std::string &enemy_naming,
                                  Dungeon &dungeon,
                                  size_t floor,
                                  std::pair<size_t, size_t> coordinates,
                                  size_t level,
                                  FRACTIONS fraction)
{
    typedef std::function<Enemy&(const std::string&, Dungeon&, size_t, std::pair<size_t, size_t>, size_t, FRACTIONS)>
            builder_func_type;

    static std::map<std::string, builder_func_type> builders_map {
            {"alive", builder_func_type(GlobalEnemyManager::buildAlive)},
            {"undead", builder_func_type(GlobalEnemyManager::buildGolem)},
            {"golem", builder_func_type(GlobalEnemyManager::buildUndead)}
    };

    if (enemy_class == "alive")
        return GlobalEnemyManager::buildAlive(enemy_naming, dungeon, floor, coordinates, level, fraction);

    else if (enemy_class == "undead")
        return GlobalEnemyManager::buildUndead(enemy_naming, dungeon, floor, coordinates, level, fraction);

    else if (enemy_class == "golem")
        return GlobalEnemyManager::buildGolem(enemy_naming, dungeon, floor, coordinates, level, fraction);

    try {
        auto &builder = builders_map.at(enemy_class);
        return builder(enemy_naming, dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::out_of_range(std::string("No enemy type to build with naming: ") + enemy_class);
    }
}

Enemy &GlobalEnemyManager::buildAlive(const std::string &enemy_naming,
                                      Dungeon & dungeon,
                                      size_t floor,
                                      std::pair<size_t, size_t> coordinates,
                                      size_t level,
                                      FRACTIONS fraction)
{
    static std::map<std::string, std::shared_ptr<AliveBuilder>> builder_map {
            {"goblin", std::make_shared<AliveBuilderAs<Goblin>>()},
            {"ogr", std::make_shared<AliveBuilderAs<Ogr>>()}
            };
    try {
        auto &builder = builder_map.at(enemy_naming);
        return builder->build(dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No alive to build with this name: ") + enemy_naming);
    }
}

Enemy &GlobalEnemyManager::buildUndead(const std::string &enemy_naming,
                                       Dungeon & dungeon,
                                       size_t floor,
                                       std::pair<size_t, size_t> coordinates,
                                       size_t level,
                                       FRACTIONS fraction)
{

    static std::map<std::string, std::shared_ptr<UndeadBuilderFromNothing>> builder_map {
            {"skeleton_goblin", std::make_shared<UndeadBuilderBase<Skeleton, Goblin>>()},
            {"skeleton_ogr", std::make_shared<UndeadBuilderBase<Skeleton, Ogr>>()},
            {"ghoul_goblin", std::make_shared<UndeadBuilderBase<Ghoul, Goblin>>()},
            {"ghoul_ogr", std::make_shared<UndeadBuilderBase<Ghoul, Ogr>>()},
            };
    try {
        auto &builder = builder_map.at(enemy_naming);
        return builder->build(dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No undead to build with this name: ") + enemy_naming);
    }
}

Enemy &GlobalEnemyManager::buildGolem(const std::string &enemy_naming,
                                      Dungeon & dungeon,
                                      size_t floor,
                                      std::pair<size_t, size_t> coordinates,
                                      size_t level,
                                      FRACTIONS fraction)
{
    static std::map<std::string, std::shared_ptr<GolemBuilder>> builder_map {
            {"stone_golem", std::make_shared<GolemBuilderAs<StoneGolemType> >()},
            {"fire_golem", std::make_shared<GolemBuilderAs<FireGolemType> >()},
            {"ethereal_golem", std::make_shared<GolemBuilderAs<EtherealGolemType> >()}
    };
    try {
        auto &builder = builder_map.at(enemy_naming);
        return builder->build(dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No golem to build with this name: ") + enemy_naming);
    }
}

const std::vector<std::string> GlobalEnemyManager::getAllTypesInEnemyClass(const std::string &enemy_class) {
    static std::map<std::string ,std::vector<std::string>> enemy_types = {
            {"golem", {"stone_golem", "fire_golem", "ethereal_golem"}},
            {"undead", {"skeleton", "ghoul"}},
            {"alive", {"goblin", "ogr"}}
    };
    try {
        return enemy_types[enemy_class];
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("No such enemy class");
    }
}


