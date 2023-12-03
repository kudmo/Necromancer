#include <MainSkill/MainSkill.h>
#include <Entity/Entity.h>
#include <Object/Object.h>


MainSkill::MainSkill(uint level): level(level) {}

const std::vector<std::string> MainSkill::getAllVariations() const noexcept{
    std::vector<std::string> var;
    var.reserve(variations.size());
    for (auto &i : variations) {
        var.push_back(i.first);
    }
    return var;
}

uint MainSkill::getCost(std::string variation)  {
    try {
        variations.at(variation)->getCost(level);
    } catch (std::out_of_range&) {
        throw skill_errors::invalid_subskill_error("No subskill with this name");
    }
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
        variations.at(variation)->skill(level, user, target);
    } catch (std::out_of_range&) {
        throw skill_errors::invalid_subskill_error(std::string("No subskill with this name: ") + variation);
    }
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

const std::string MainSkill::getInfo() const noexcept {
    std::string res;
    res += "{";
    res += R"("naming" : )";
    res += "\"" + getName() + "\", ";
    res += R"("level" : )" + std::to_string(level) + ",";
    res +=  R"("variations_count" : )" + std::to_string(variations.size()) + ", ";
    res +=  R"("variations" : )";
    res += "[";
    size_t s = 0;
    size_t c = variations.size();
    for (auto &i: variations) {
        res += "{";
        res += R"("naming" : )";
        res += "\"" + i.first + "\"";
        res += "}";
        if (s < c -1)
            res += ", ";
        ++s;
    }
    res += "]";
    res += "}";
    return res;
}






