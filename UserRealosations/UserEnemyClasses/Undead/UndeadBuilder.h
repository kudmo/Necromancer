#ifndef LAB3_UNDEADBUILDER_H
#define LAB3_UNDEADBUILDER_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"

#include "Undead.h"

template <T> requires std::is_same<T,UndeadType>
class UndeadBuilder{
public:
    Enemy * CreateUndead(uint level, AliveType *dead) {
        T *type = new T(level, dead);
        Undead *a = new Alive(*T);
        return dynamic_cast<Enemy*>(a);
    }
};

#endif //LAB3_UNDEADBUILDER_H
