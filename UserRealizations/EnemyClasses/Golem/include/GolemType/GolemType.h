#ifndef LAB3_GOLEMTYPE_H
#define LAB3_GOLEMTYPE_H

#include <cstdlib>
#include <EnemyType/EnemyType.h>


class GolemType : public EnemyType {
public:
    explicit GolemType(uint level);
    virtual uint calculateIgnoringProbability(uint level) const {return 0;};
    uint getIgnoringProbability() const;
};

#endif //LAB3_GOLEMTYPE_H
