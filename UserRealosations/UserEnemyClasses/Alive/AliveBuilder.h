#ifndef LAB3_ALIVEBUILDER_H
#define LAB3_ALIVEBUILDER_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"
#include "../../../BaseInterfaces/Entity/include/Entity/Entity.h"
#include "Alive.h"

template <T> requires  std::is_same<T, AliveType>
class AliveBuilder {
public:
    Enemy * CreateEnemy(uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level);
        Alive *a = new Alive(*T, fraction);
        //! @todo возможно тут ссылка
        return dynamic_cast<Enemy*>(a);
    }
};
#endif //LAB3_ALIVEBUILDER_H
