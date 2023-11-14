#ifndef LAB3_DEADBODY_H
#define LAB3_DEADBODY_H

#include "../../../BaseInterfaces/Items/include/Item/Item.h"
#include "../../../BaseInterfaces/EnemyType/include/EnemyType/EnemyType.h"
#include "../../UserEnemyTypes/AliveType/AliveType.h"

#include "../../../BaseInterfaces/Interfaces/IRevivable.h"
class DeadBody : public Item {
private:
    AliveType *who_it_was;
public:
    DeadBody(AliveType* a) : who_it_was(a) {};

    //! @todo а не константный ли указатель?
    const AliveType *getType() const {
        return who_it_was;
    }
    AliveType *takeBody() {
        auto temp = who_it_was;
        who_it_was = nullptr;
        return temp;
    }

    ~DeadBody() = default;
};

#endif //LAB3_DEADBODY_H
