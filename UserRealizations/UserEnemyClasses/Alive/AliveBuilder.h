#ifndef LAB3_ALIVEBUILDER_H
#define LAB3_ALIVEBUILDER_H

#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"
#include "../../../BaseInterfaces/Entity/include/Entity/Entity.h"

#include "Alive.h"

template <class T> requires std::is_same<T, AliveType>
class AliveBuilder {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level);
        Alive *a = new Alive(f, coord, type, fraction);
        f.addEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_ALIVEBUILDER_H
