#ifndef LAB3_ALIVETYPE_H
#define LAB3_ALIVETYPE_H

#include <utility>

#include "../../../BaseInterfaces/EnemyType/include/EnemyType/EnemyType.h"


class AliveType : public EnemyType {
public:
    AliveType(uint level);
};

#endif //LAB3_ALIVETYPE_H
