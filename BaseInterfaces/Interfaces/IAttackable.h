#ifndef LAB3_IATTACKABLE_H
#define LAB3_IATTACKABLE_H

#include <utility>
#include <cstdlib>

#include <IAttacker.h>

class IAttacker;

/*!
 * @brief The interface of everything that can be attacked
 */
class IAttackable {
public:
    /*!
     * @param attacker The one who attacked
     * @param damage Damage done
     */
    virtual void damaged(IAttacker& attacker, uint damage) = 0;
};

#endif //LAB3_IATTACKABLE_H
