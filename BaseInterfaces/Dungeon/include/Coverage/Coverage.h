#ifndef LAB3_COVERAGE_H
#define LAB3_COVERAGE_H

#include <string>

#include "../../../Interfaces/IAttacker.h"

#include "../../../Entity/include/Entity/Entity.h"

class Entity;

class Coverage {
public:
    virtual bool isPassable() = 0;
    virtual void effect(Entity&) = 0;
    virtual ~Coverage() = default;
};
#endif //LAB3_COVERAGE_H
