#ifndef LAB3_GOLEMTYPE_H
#define LAB3_GOLEMTYPE_H

#include <utility>

#include "../../../BaseInterfaces/EnemyType/include/EnemyType/EnemyType.h"


class GolemType : public EnemyType {
public:
    GolemType(uint level);
    virtual uint calculateIgnoringProbability(uint level) const;
    uint getIgnoringProbability() const;
};

#endif //LAB3_GOLEMTYPE_H
