#ifndef LAB3_GLOBALENEMYMANAGER_H
#define LAB3_GLOBALENEMYMANAGER_H

#include "Enemy/Enemy.h"
class Dungeon;

class GlobalEnemyManager {
private:
    static Enemy &buildAlive(const std::string &, Dungeon &, size_t, std::pair<size_t, size_t>, size_t, FRACTIONS fractions = FRACTIONS::ENEMY);
    static Enemy &buildUndead(const std::string &, Dungeon &, size_t, std::pair<size_t, size_t>, size_t, FRACTIONS fractions = FRACTIONS::ENEMY);
    static Enemy &buildGolem(const std::string &, Dungeon &, size_t , std::pair<size_t, size_t>, size_t, FRACTIONS fractions = FRACTIONS::ENEMY);
public:
    static Enemy &build(const std::string &, const std::string &, Dungeon &, size_t, std::pair<size_t, size_t>, size_t, FRACTIONS fractions = FRACTIONS::ENEMY);
};


#endif //LAB3_GLOBALENEMYMANAGER_H
