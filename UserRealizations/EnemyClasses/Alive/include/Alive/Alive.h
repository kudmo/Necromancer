#ifndef LAB3_ALIVE_H
#define LAB3_ALIVE_H

#include <utility>

#include "ISummoner.h"
#include <Enemy/Enemy.h>
#include "Dungeon/Dungeon.h"
#include <AliveType/AliveType.h>

class Alive : public Enemy, public ISummoner {
public:
    Alive(Floor& f, std::pair<size_t,size_t> coord, AliveType* type, FRACTIONS fraction);
    const std::string getFullInfo() const override;
    const std::string getType() const override {return "alive";}
    void die() override;
};

class AliveBuilder {
public:
    virtual Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const = 0;
};

template <class T> requires std::is_base_of_v<AliveType, T>
class AliveBuilderAs : public AliveBuilder {
public:
    Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const override {
        auto &f = dungeon.floorByNumber(floor);
        f.getByCoord(coord);
        T *type = new T(level);
        auto *a = new Alive(f, coord, type, fraction);
        f.summonEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};


#endif //LAB3_ALIVE_H
