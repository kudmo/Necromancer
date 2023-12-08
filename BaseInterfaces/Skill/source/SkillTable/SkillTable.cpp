#include <SkillTable/SkillTable.h>
#include <MainSkill/MainSkill.h>


void SkillTable::addSkill(std::unique_ptr<MainSkill>&& skill) {
    if (skills.count(skill->getName()) != 0)
        throw skill_errors::invalid_subskill_error(std::string("Skill with this name already exists"));
    skills.emplace(skill->getName(), std::move(skill));
}

void SkillTable::addSkillVariation(std::string main, std::unique_ptr<SubSkill>&& subskill) {
    skills.at(main)->addVariation(std::move(subskill));
}

const std::vector<std::string> SkillTable::getAllSkills() const {
    std::vector<std::string> names;
    names.reserve(skills.size());
    for (auto &skill : skills )
        names.push_back(skill.first);
    return names;
}

const std::map<std::string, std::vector<std::string>> SkillTable::getAllVariations() const {
    std::map<std::string, std::vector<std::string>> res;
    for (auto &i : skills) {
        res.emplace(i.first, i.second->getAllVariations());
    }
    return res;
}

void SkillTable::upgradeSkill(std::string name) {
    skills.at(name)->upgrade();
}

uint SkillTable::getCost(std::string name, std::string subname, const Object& o) const {
    try {
        auto &skill = skills.at(name);
        return skill->getCost(subname, o);
    } catch (std::out_of_range&) {
        throw skill_errors::skill_table_no_skill_error(std::string("No skill with this name"));
    }
}

void SkillTable::useSkill(std::string name, std::string subname, Entity &user, Object &target)  {
    try {
        auto &skill = skills.at(name);
        skill->useVariation(subname, user, target);
    } catch (std::out_of_range&) {
        throw skill_errors::skill_table_no_skill_error(std::string("No skill with this name"));
    }
}

//SkillTable::~SkillTable() {}

const std::string SkillTable::getInfo() const noexcept {
    std::string res;
    res += "{";
    res += R"("skill_cont" : )" + std::to_string(skills.size()) + ", ";
    res += R"("skills" : )";
    res += "[";
    size_t s = 0;
    size_t c = skills.size();
    for (auto &i : skills) {
        res += i.second->getInfo();
        if (s < c - 1)
            res += ", ";
        ++s;
    }
    res += "]";
    res += "}";
    return res;
}

SkillTable &SkillTable::operator=(SkillTable &&moved) noexcept {
    if (&moved != this)
        std::swap(moved.skills, skills);
    return *this;
}



