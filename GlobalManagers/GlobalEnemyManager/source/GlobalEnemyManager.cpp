#include <GlobalEnemyManager.h>

#include "Dungeon/Dungeon.h"
#include <Alive/Alive.h>
#include "Undead/Undead.h"
#include "Golem/Golem.h"


GlobalEnemyManager::GlobalEnemyManager(std::string path) {
    aliveManager = std::make_unique<AliveManager>(path + "/alive");
    undeadManager = std::make_unique<UndeadManager>(path + "/undead");
    golemManager = std::make_unique<GolemManager>(path + "/golem");
}

Enemy &GlobalEnemyManager::buildAlive(const std::string &name, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord,
                                      size_t level, FRACTIONS fraction) const {
    return aliveManager->build(name, dungeon, floor, coord, level, fraction);
}

Enemy &GlobalEnemyManager::buildUndead(const std::string &name, const std::string &name_dead, Dungeon &dungeon, size_t floor,
                                std::pair<size_t, size_t> coord, size_t level, FRACTIONS fraction) const {
    auto dead = aliveManager->buildType(name_dead, level);
    return undeadManager->build(name, dungeon, floor, coord, level, std::move(dead), fraction);
}

Enemy &GlobalEnemyManager::buildGolem(const std::string &name, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord,
                               size_t level, FRACTIONS fraction) const {
    return golemManager->build(name, dungeon, floor, coord, level, fraction);
}

Enemy &GlobalEnemyManager::build(const std::string &type, const std::string &fullname, Dungeon &dungeon, size_t floor,
                                 std::pair<size_t, size_t> coord, size_t level, FRACTIONS fraction) const {
    if (type == "alive") {
        return buildAlive(fullname,dungeon, floor, coord, level, fraction);
    } else if (type == "golem") {
        return buildGolem(fullname, dungeon, floor, coord, level, fraction);
    } else if (type == "undead") {
        auto undead_name = fullname.substr(0, fullname.find("_"));
        auto alive_name = fullname.substr(fullname.find("_") + 1);
        return buildUndead(undead_name, alive_name, dungeon, floor, coord, level, fraction);
    }
}


const std::vector<std::string> GlobalEnemyManager::getAllAliveTypes() {
    return aliveManager->getAllAliveTypes();
}

const std::vector<std::string> GlobalEnemyManager::getAllUndeadTypes() {
    return undeadManager->getAllUndeadTypes();
}

const std::vector<std::string> GlobalEnemyManager::getAllGolemTypes() {
    return golemManager->getAllGolemTypes();
}

std::unique_ptr<SubSkill> GlobalEnemyManager::buildNecromancy(const std::string &name) {
    return undeadManager->buildNecromancy(name);
}

std::unique_ptr<SubSkill> GlobalEnemyManager::buildMorphism(const std::string &name) {
    return undeadManager->buildMorphism(name);
}

