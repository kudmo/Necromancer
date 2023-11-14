#ifndef LAB3_MAGMA_H
#define LAB3_MAGMA_H

#include <utility>
#include "../../../BaseInterfaces/Dungeon/include/Coverage/Coverage.h"
#include "../../../BaseInterfaces/Interfaces/IAttacker.h"
#include "../../../BaseInterfaces/Interfaces/IAttackable.h"

class Magma : public Coverage, private IAttacker {
private:
    uint damage = 10;
    void attack(IAttackableI&) override {;}
public:
    Magma() = default;
    bool isPassable() override {return true;};
    void effect(Entity &e) override {
        e.damaged(*this, damage);
    }
    ~Magma() override;
};


#endif //LAB3_MAGMA_H
