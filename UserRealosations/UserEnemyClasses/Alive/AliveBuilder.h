#ifndef LAB3_ALIVEBUILDER_H
#define LAB3_ALIVEBUILDER_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"

#include "Alive.h"

template <T> requires  std::is_same<T,AliveType>
class AliveBuilder {
public:
    Enemy * CreateAlive(uint level) {
        T *type = new T(level);
        Alive *a = new Alive(*T);
        return dynamic_cast<Enemy*>(a);
    }
};
#endif //LAB3_ALIVEBUILDER_H
