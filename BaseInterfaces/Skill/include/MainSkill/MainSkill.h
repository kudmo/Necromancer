#pragma once

#include <map>
#include <string>

#include "../SubSkill/SubSkill.h"
#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"
#include "../Exeptions/SkillException.h"

class MainSkill {
private:
    const uint max_level = 10;
    uint level = 1;
    std::map<std::string, SubSkill*> variations;
    std::string def;
public:
    MainSkill(uint level, SubSkill& def): level(level) {
        this->def = def.getName();
        variations = std::map<std::string, SubSkill*>;
        variations.emplace(this->def, &def);
    }

    virtual void checkVariation(SubSkill* ) = 0;
    virtual void checkUser(Entity *) = 0;
    virtual void checkTarget(Object *) = 0;

    virtual std::string getName() = 0;

    const std::vector<std::string> getAllVariations() const {
        std::vector<std::string> var;
        var.reserve(variations.size());
        for (auto &i : variations) {
            var.push_back(i.first);
        }
        return var;
    }

    uint getCost(std::string variation) {
        //! @todo Не забыть про перерасчёт в зависимоти от уровня
        //! @todo Не забыть проверку на наличие
        return variations.at(variation)->getCost();
    }
    /*!
     * @throws skill_errors::invalid_subskill_error if Subskill with this name already was added
     */
    void addVariation(SubSkill* s) {
        checkVariation(s);
        if (variations.count(s->getName()) != 0)
            throw skill_errors::invalid_subskill_error(std::string("Subskill with this name already exists"))
        variations.emplace(s->getName(), s);
    };

    /*!
     * @throws skill_errors::invalid_subskill_error if no subskill with this name
     */
    void useVariation(std::string variation, Entity& user, Object& target) {
        checkUser(&user);
        checkTarget(&target);
        try {
            variations.at(variation)->skill(user, target);
        } catch (std::out_of_range) {
            throw skill_errors::invalid_subskill_error("No subskill with this name");
        }
    };

    void useDefault(Entity& user, Object& target) {
        useVariation(def, user, target);
    };

    /*!
     * @throws skill_errors::invalid_skill_level if current level is max
     */
    virtual void upgrade() {
        if (level >= max_level)
            throw skill_errors::invalid_skill_level(std::string("Max skill level is ") + std::to_string(max_level));
        level++;
    };
};