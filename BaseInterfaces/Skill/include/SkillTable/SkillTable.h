#pragma once

#include <map>
#include <string>

#include "../MainSkill/MainSkill.h"
#include "../SubSkill/SubSkill.h"
#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"


class SkillTable {
private:
    //!@todo поменять на wrapper std::reference_wrapper (<functional>)
    std::map<std::string, MainSkill&> skills;
public:
    void addSkill(MainSkill&);
    void addSkillVariation(std::string, SubSkill&);

    const std::vector<std::string> getAllSkills() const {
        std::vector<std::string> names;
        names.reserve(skills.size());
        for (auto skill : skills )
            names.push_back(skill.first);
        return names;
    }

    const std::map<std::string, std::vector<std::string>> getAllVariations() const {
        std::map<std::string, std::vector<std::string>> res;
        for (auto &i : skills) {
            res.emplace(i.first,i.second.getAllVariations());
        }
        return res;
    }

    void upgradeSkill(std::string name) {
        skills.at(name).upgrade();
    }
    void useSkill(std::string name, Entity& user, Object& target) {
        try {
            MainSkill& skill = skills.at(name);
            skill.useDefault(user, target);
        } catch (std::out_of_range) {
            throw skill_errors::skill_table_no_skill_error("No skill with this name");
        }
    }
    void useSkillVariation(std::string name, std::string subname, Entity& user, Object& target) {
        try {
            MainSkill &skill = skills.at(name);
            skill.useVariation(subname, user, target);
        }
    }
};