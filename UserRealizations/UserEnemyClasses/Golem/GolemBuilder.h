#ifndef LAB3_GOLEMBUILDER_H
#define LAB3_GOLEMBUILDER_H

#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"
#include "../../../BaseInterfaces/Entity/include/Entity/Entity.h"

#include "Golem.h"

template <class T> requires std::is_same<T, GolemType>
class GolemBuilder {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level);
        Alive *a = new Alive(f, coord, type, fraction);
        f.addEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_GOLEMBUILDER_H
