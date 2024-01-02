#ifndef LAB3_GLOBALENEMYMANAGER_H
#define LAB3_GLOBALENEMYMANAGER_H

#include "Enemy/Enemy.h"
#include "AliveManager.h"
#include "UndeadManager.h"
#include "GolemManager.h"

#include "SubSkill/SubSkill.h"
#include "MorphismVariations/MorphismVariation.h"
#include "NecromancyVariations/NecromancyVariation.h"

#include <vector>

class Dungeon;

class GlobalEnemyManager {
private:
    std::unique_ptr<AliveManager> aliveManager;
    std::unique_ptr<UndeadManager> undeadManager;
    std::unique_ptr<GolemManager> golemManager;

    GlobalEnemyManager(std::string path = "plugins/Enemy");
    GlobalEnemyManager(const GlobalEnemyManager&) = delete;
    GlobalEnemyManager(GlobalEnemyManager&&) = delete;
public:
    static GlobalEnemyManager& getInstance() {
        static GlobalEnemyManager manager;
        return manager;
    }

    Enemy &buildAlive(const std::string &name, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord, size_t level, FRACTIONS fraction = FRACTIONS::ENEMY) const;
    Enemy &buildUndead(const std::string &name,const std::string &name_dead, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord, size_t level, FRACTIONS fraction = FRACTIONS::ENEMY) const;
    Enemy &buildGolem(const std::string &name, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord, size_t level, FRACTIONS fraction = FRACTIONS::ENEMY) const;

    std::unique_ptr<SubSkill> buildNecromancy(const std::string &);
    std::unique_ptr<SubSkill> buildMorphism(const std::string &);

    Enemy &build (const std::string &type, const std::string &fullname, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord, size_t level, FRACTIONS fraction = FRACTIONS::ENEMY) const;

    const std::vector<std::string> getAllAliveTypes();
    const std::vector<std::string> getAllUndeadTypes();
    const std::vector<std::string> getAllGolemTypes();
};


#endif //LAB3_GLOBALENEMYMANAGER_H
