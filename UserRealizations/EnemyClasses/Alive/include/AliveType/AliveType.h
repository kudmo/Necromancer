#ifndef LAB3_ALIVETYPE_H
#define LAB3_ALIVETYPE_H

#include <cstdlib>

#include <EnemyType/EnemyType.h>

class AliveType : public EnemyType {
public:
    explicit AliveType(uint level);
};

#endif //LAB3_ALIVETYPE_H