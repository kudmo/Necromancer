#ifndef LAB3_IATTACKER_H
#define LAB3_IATTACKER_H

#include <utility>

#include <IAttackable.h>

class IAttackable;

class IAttacker {
    virtual void attack(IAttackable&) = 0;
};

#endif //LAB3_IATTACKER_H
