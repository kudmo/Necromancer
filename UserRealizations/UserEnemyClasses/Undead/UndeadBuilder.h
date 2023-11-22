#ifndef LAB3_UNDEADBUILDER_H
#define LAB3_UNDEADBUILDER_H

#include "../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../BaseInterfaces/Enemy/include/Enemy/EnemyBuilder.h"
#include "../../../BaseInterfaces/Entity/include/Entity/Entity.h"
#include "Undead.h"

template <class T>// requires std::is_same<T,UndeadType>
class UndeadBuilder {
public:
    Enemy& CreateUndead(Floor& f, std::pair<size_t,size_t> coord, uint level, AliveType *dead, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level, dead);
        Undead *a = new Undead(f, coord, type, fraction);
        f.addEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};

#endif //LAB3_UNDEADBUILDER_H
