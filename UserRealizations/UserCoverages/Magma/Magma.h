#ifndef LAB3_MAGMA_H
#define LAB3_MAGMA_H

#include <utility>

#include "../../../BaseInterfaces/Interfaces/IAttacker.h"
#include "../../../BaseInterfaces/Interfaces/IAttackable.h"

#include "../../../BaseInterfaces/Dungeon/include/Coverage/Coverage.h"

class Magma : public Coverage, private IAttacker {
private:
    uint damage = 10;
    void attack(IAttackable&) override {}
public:
    Magma() = default;
    bool isPassable() override;
    void effect(Entity &e) override;
};


#endif //LAB3_MAGMA_H
