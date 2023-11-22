#ifndef LAB3_DEADBODY_H
#define LAB3_DEADBODY_H

#include <utility>

#include "../../../BaseInterfaces/Items/include/Item/Item.h"
#include "../../../BaseInterfaces/EnemyType/include/EnemyType/EnemyType.h"
#include "../../UserEnemyTypes/AliveType/AliveType.h"

#include "../../../BaseInterfaces/Interfaces/IRevivable.h"

class DeadBody : public Item {
private:
    AliveType* who_it_was;
public:
    DeadBody( Floor& f, std::pair<size_t,size_t> coord, AliveType* a);

    const AliveType &getType() const;

    AliveType *takeBody();
    ~DeadBody() = default;
};

#endif //LAB3_DEADBODY_H
