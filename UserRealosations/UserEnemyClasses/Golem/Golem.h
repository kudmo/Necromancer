#ifndef LAB3_GOLEM_H
#define LAB3_GOLEM_H


#include "../../UserEnemyTypes/GolemType/GolemType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"

class Golem : public  Enemy {
public:
    uint getIgnoringProbability() const;
    uint damaged(uint) override;
};
#endif //LAB3_GOLEM_H
