#ifndef LAB3_UNDEAD_H
#define LAB3_UNDEAD_H

#include <ISummoner.h>

#include <Enemy/Enemy.h>
#include <UndeadType/UndeadType.h>

class Undead : public Enemy, public ISummoner {
public:
    Undead(Floor& f, std::pair<size_t,size_t> coord, UndeadType* type, FRACTIONS fraction);

    void die() override;
};

template <class T> requires std::is_base_of_v<UndeadType, T>
class UndeadBuilder {
public:
    Enemy& CreateUndead(Floor& f, std::pair<size_t,size_t> coord, uint level, AliveType &dead, FRACTIONS fraction = FRACTIONS::ENEMY) {
        T *type = new T(level, dead);
        auto *a = new Undead(f, coord, type, fraction);
        f.summonEntity(*a);
        return static_cast<Enemy&>(*a);
    }
};
#endif //LAB3_UNDEAD_H
