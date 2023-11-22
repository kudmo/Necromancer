#ifndef LAB3_IATTACKABLE_H
#define LAB3_IATTACKABLE_H

#include <utility>
#include <cstdint>
#include <cstdlib>
#include "IAttacker.h"

class IAttacker;

class IAttackable {
public:
    virtual uint damaged(IAttacker&, uint) = 0;

};

#endif //LAB3_IATTACKABLE_H
