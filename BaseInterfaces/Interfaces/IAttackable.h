#ifndef LAB3_IATTACKABLE_H
#define LAB3_IATTACKABLE_H

#include <utility>
#include "IAttacker.h"

class IAttackable {
public:
    virtual uint damaged(IAttacker&, uint) = 0;
};

#endif //LAB3_IATTACKABLE_H
