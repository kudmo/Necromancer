#include <MainSkill/MainSkill.h>
#include <Entity/Entity.h>
#include <Object/Object.h>


MainSkill::MainSkill(uint level): level(level) {}

MainSkill::MainSkill(std::map<std::string, SubSkill*> skills): variations(std::move(skills)) {}

void MainSkill::setDefault(std::string def) {
    if (variations.count(def) == 0)
        throw skill_errors::skill_table_no_skill_error("No skill with this name");
    this->def = def;
}

const std::vector<std::string> MainSkill::getAllVariations() const noexcept{
    std::vector<std::string> var;
    var.reserve(variations.size());
    for (auto &i : variations) {
        var.push_back(i.first);
    }
    return var;
}

uint MainSkill::getCost(std::string variation)  {
    //! @todo Не забыть про перерасчёт в зависимоти от уровня
    //! @todo Не забыть проверку на наличие
    return variations.at(variation)->getCost();
}

void MainSkill::addVariation(SubSkill *s)  {
    checkVariation(s);
    if (variations.count(s->getName()) != 0)
        throw skill_errors::invalid_subskill_error(std::string("Subskill with this name already exists"));

    variations.emplace(s->getName(), s);
};

void MainSkill::useVariation(std::string variation, Entity &user, Object &target) {
    checkUser(&user);
    checkTarget(&target);
    try {
        variations.at(variation)->skill(user, target);
    } catch (std::out_of_range&) {
        throw skill_errors::invalid_subskill_error("No subskill with this name");
    }
};

void MainSkill::useDefault(Entity &user, Object &target)  {
    useVariation(def, user, target);
};

void MainSkill::upgrade()  {
    if (level >= max_level)
        throw skill_errors::invalid_skill_level(std::string("Max skill level is ") + std::to_string(max_level));
    level++;
}

MainSkill::~MainSkill() {
    for (auto &i : variations) {
        delete i.second;
    }
}






