#ifndef LAB3_ALIVE_H
#define LAB3_ALIVE_H

#include <utility>

#include "ISummoner.h"
#include <Enemy/Enemy.h>

#include <AliveType/AliveType.h>

class Alive : public Enemy, public ISummoner {
public:
    Alive(Floor& f, std::pair<size_t,size_t> coord, AliveType* type, FRACTIONS fraction);

    void die() override;
};

template <class T> requires std::is_base_of_v<AliveType, T>
class AliveBuilder {
public:
    Enemy& CreateEnemy(Floor& f, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level);
        auto *a = new Alive(f, coord, type, fraction);
        f.summonEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};

#endif //LAB3_ALIVE_H
