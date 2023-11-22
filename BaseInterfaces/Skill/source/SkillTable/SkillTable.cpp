#include "../../include/SkillTable/SkillTable.h"

SkillTable::SkillTable(std::map<std::string, MainSkill &> skills)  : skills(skills) {}

void SkillTable::addSkill(MainSkill &skill) {
    if (skills.count(skill.getName()) != 0)
        throw skill_errors::invalid_subskill_error(std::string("Skill with this name already exists"));
    skills.emplace(skill.getName(), skill);
}

void SkillTable::addSkillVariation(std::string main, SubSkill *subskill) {
    skills.at(main).addVariation(subskill);
}

const std::vector<std::string> SkillTable::getAllSkills() const {
    std::vector<std::string> names;
    names.reserve(skills.size());
    for (auto skill : skills )
        names.push_back(skill.first);
    return names;
}

const std::map<std::string, std::vector<std::string>> SkillTable::getAllVariations() const {
    std::map<std::string, std::vector<std::string>> res;
    for (auto &i : skills) {
        res.emplace(i.first,i.second.getAllVariations());
    }
    return res;
}

void SkillTable::upgradeSkill(std::string name) {
    skills.at(name).upgrade();
}

void SkillTable::useSkill(std::string name, Entity &user, Object &target) {
    try {
        MainSkill& skill = skills.at(name);
        skill.useDefault(user, target);
    } catch (std::out_of_range) {
        throw skill_errors::skill_table_no_skill_error("No skill with this name");
    }
}

void SkillTable::useSkillVariation(std::string name, std::string subname, Entity &user, Object &target)  {
    try {
        MainSkill &skill = skills.at(name);
        skill.useVariation(subname, user, target);
    } catch (std::out_of_range) {
        throw skill_errors::skill_table_no_skill_error(std::string("No skill with this name"));
    }
}


