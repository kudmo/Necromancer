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


Enemy & GlobalEnemyManager::build(const std::string &type,
                                  const std::string &naming,
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

    if (type == "alive")
        return GlobalEnemyManager::buildAlive(naming, dungeon, floor, coordinates, level, fraction);

    else if (type == "undead")
        return GlobalEnemyManager::buildUndead(naming, dungeon, floor, coordinates, level, fraction);

    else if (type == "golem")
        return GlobalEnemyManager::buildGolem(naming, dungeon, floor, coordinates, level, fraction);

    try {
        auto &builder = builders_map.at(type);
        return builder(naming, dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::out_of_range(std::string("No enemy type to build with naming: ") + type);
    }
}

Enemy &GlobalEnemyManager::buildAlive(const std::string &naming,
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
        auto &builder = builder_map.at(naming);
        return builder->build(dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No alive to build with this name: ") + naming);
    }
}

Enemy &GlobalEnemyManager::buildUndead(const std::string &naming,
                                       Dungeon & dungeon,
                                       size_t floor,
                                       std::pair<size_t, size_t> coordinates,
                                       size_t level,
                                       FRACTIONS fraction)
{

    static std::map<std::string, std::shared_ptr<UndeadBuilderFromNothing>> builder_map {
            {"skeleton-goblin", std::make_shared<UndeadBuilderBase<Skeleton, Goblin>>()},
            {"skeleton-ogr", std::make_shared<UndeadBuilderBase<Skeleton, Ogr>>()},
            {"ghoul-goblin", std::make_shared<UndeadBuilderBase<Ghoul, Goblin>>()},
            {"ghoul-ogr", std::make_shared<UndeadBuilderBase<Ghoul, Ogr>>()},
            };
    try {
        auto &builder = builder_map.at(naming);
        return builder->build(dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No undead to build with this name: ") + naming);
    }
}

Enemy &GlobalEnemyManager::buildGolem(const std::string &naming,
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
        auto &builder = builder_map.at(naming);
        return builder->build(dungeon, floor, coordinates, level, fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No golem to build with this name: ") + naming);
    }
}


