#pragma once

#include <map>
#include <string>

#include "../MainSkill/MainSkill.h"
#include "../SubSkill/SubSkill.h"
#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"


class SkillTable {
private:
    std::map<std::string, MainSkill&> skills;
public:
    void addSkill(MainSkill&);
    void addSkillVariation(std::string, SubSkill&);
    void upgradeSkill(std::string);
    void useSkill(std::string, Entity&, Object&);
    void useSkillVariation(std::string, std::string, Entity&, Object&);
};