#ifndef LAB3_COVERAGE_H
#define LAB3_COVERAGE_H

#include <string>
#include "../../../Entity/include/Entity/Entity.h"

class Coverage {
public:
    virtual bool isPassable() = 0;
    virtual void Effect(Entity&) = 0;
    virtual std::string getNaming() = 0;
};
#endif //LAB3_COVERAGE_H
