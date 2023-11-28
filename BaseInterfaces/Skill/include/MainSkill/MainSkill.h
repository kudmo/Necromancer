#pragma once

#include <map>
#include <memory>
#include <string>
#include <exception>
#include <vector>

#include <SubSkill/SubSkill.h>

#include <Exceptions/SkillExceptions.h>

class Object;
class Entity;

class MainSkill {
private:
    const uint max_level = 10;
    uint level = 1;
    std::map<std::string, SubSkill*> variations;
    std::string def;
public:
    MainSkill() = default;
    explicit MainSkill(uint level);
    explicit MainSkill(std::map<std::string, SubSkill*> skills);


    void setDefault(std::string def);

    /*!
     * @throws skill_errors::invalid_subskill_type_error if this subskill isn't variation of this skill
     */
    virtual void checkVariation(SubSkill* ) = 0;
    /*!
     * @throws skill_errors::invalid_skill_user if user can't use this skill
     */
    virtual void checkUser(Entity *) = 0;
    /*!
     * @throws skill_errors::invalid_skill_target if this skill can't be used on this target
     */
    virtual void checkTarget(Object *) = 0;

    virtual std::string getName() noexcept = 0;

    const std::vector<std::string> getAllVariations() const noexcept;

    uint getCost(std::string variation);

    /*!
     * @throws skill_errors::invalid_subskill_error if Subskill with this name already was added
     */
    void addVariation(SubSkill* s);

    /*!
     * @throws skill_errors::invalid_subskill_error if no subskill with this name
     */
    void useVariation(std::string variation, Entity& user, Object& target);

    void useDefault(Entity& user, Object& target);

    /*!
     * @throws skill_errors::invalid_skill_level if current level is max
     */
    virtual void upgrade();
    virtual ~MainSkill();
};