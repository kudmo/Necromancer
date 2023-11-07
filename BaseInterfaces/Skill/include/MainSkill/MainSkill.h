#pragma once

#include <map>
#include <string>

#include "../SubSkill/SubSkill.h"
#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"

class MainSkill {
private:
    uint level;
    std::map<std::string, SubSkill&> variations;
public:
    virtual void addVariation(SubSkill&) = 0;
    virtual void useDefault(Entity&, Object&) = 0;
    virtual void useVariation(std::string, Entity&, Object&) = 0;
    virtual void upgrade() = 0;
};