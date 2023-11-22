#pragma once

#include <string>

#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"

class SubSkill {
public:
    //! @todo Подумать о том, нужен ли этот метод (нужен)
    virtual void Upgrade();
    virtual uint getCost() = 0;
    virtual std::string getName() = 0;
    virtual void skill(Entity&, Object&) = 0;
    virtual ~SubSkill() = default;
};