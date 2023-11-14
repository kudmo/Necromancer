#ifndef LAB3_UNDEADBUILDER_H
#define LAB3_UNDEADBUILDER_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"
#include "../../../BaseInterfaces/Entity/include/Entity/Entity.h"
#include "Undead.h"

template <T> requires std::is_same<T,UndeadType>
class UndeadBuilder {
public:
    Enemy * CreateUndead(uint level, AliveType *dead, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level, dead);
        Undead *a = new Undead(*T, fraction);
        return dynamic_cast<Enemy*>(a);
    }
};

#endif //LAB3_UNDEADBUILDER_H
