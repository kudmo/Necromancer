#ifndef LAB3_UNDEADTYPE_H
#define LAB3_UNDEADTYPE_H

#include <utility>

#include "../../../BaseInterfaces/EnemyType/include/EnemyType/EnemyType.h"

#include "../AliveType/AliveType.h"

class UndeadType : public  EnemyType {
private:
    AliveType *who_it_was;
public:
    UndeadType(uint level, AliveType* who): EnemyType(level) { who_it_was = who;}
    const AliveType *getWhoItWas() const;
    virtual uint CalculateCoefficient(uint level);
    uint getCoefficient();
};
#endif //LAB3_UNDEADTYPE_H
