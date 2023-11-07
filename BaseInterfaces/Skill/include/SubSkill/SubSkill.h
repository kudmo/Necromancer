#pragma once

#include <string>

#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"

class SubSkill {
public:
    virtual std::string getName() = 0;
    virtual void skill(Entity&, Object&) = 0;
};