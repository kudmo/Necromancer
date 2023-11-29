#ifndef LAB3_MAGMA_H
#define LAB3_MAGMA_H

#include <cstdlib>

#include "IAttacker.h"
#include "IAttackable.h"

#include "Coverage/Coverage.h"
#include "Entity/Entity.h"

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
