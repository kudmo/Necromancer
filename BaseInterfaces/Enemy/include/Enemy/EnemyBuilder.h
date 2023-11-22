#ifndef LAB3_ENEMYBUILDER_H
#define LAB3_ENEMYBUILDER_H

#include <utility>
#include "Enemy.h"

class EnemyBuilder {
public:
    virtual Enemy* CreateEnemy(uint level) = 0;
};

#endif //LAB3_ENEMYBUILDER_H
