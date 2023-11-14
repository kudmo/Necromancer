#ifndef LAB3_ALIVETYPE_H
#define LAB3_ALIVETYPE_H

#include <utility>

#include "../../../BaseInterfaces/EnemyType/include/EnemyType/EnemyType.h"
#include "../../../BaseInterfaces/Interfaces/IRevivable.h"

class AliveType : public EnemyType, public IRevivable {
public:
    AliveType(uint level): EnemyType(level) {};
};

#endif //LAB3_ALIVETYPE_H
