#ifndef LAB3_IATTACKER_H
#define LAB3_IATTACKER_H

#include <utility>

#include <IAttackable.h>

class IAttackable;
/*!
 * @brief The interface of everything that can attack
 */
class IAttacker {
    /*!
     * @brief Attack something that can be attacked
     * @param target The target  of the attack
     */
    virtual void attack(IAttackable& target) = 0;
};

#endif //LAB3_IATTACKER_H
