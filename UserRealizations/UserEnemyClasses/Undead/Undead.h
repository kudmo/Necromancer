#ifndef LAB3_UNDEAD_H
#define LAB3_UNDEAD_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/Enemy.h"
#include "../../../BaseInterfaces/Interfaces/ISummoner.h"

class Undead : public Enemy, public ISummoner {
public:
    Undead(Floor& f, std::pair<size_t,size_t> coord, UndeadType* type, FRACTIONS fraction);

    void die() override;
};

#endif //LAB3_UNDEAD_H
