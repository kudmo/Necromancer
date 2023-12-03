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
    //!@todo Проверка доступности цели?
private:
    const uint max_level = 10;
    uint level = 1;
    std::map<std::string, SubSkill*> variations;
public:
    MainSkill() = default;
    explicit MainSkill(uint level);


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

    virtual const std::string getName() const noexcept = 0;
    const std::string getInfo() const noexcept;

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

    /*!
     * @throws skill_errors::invalid_skill_level if current level is max
     */
    virtual void upgrade();
    virtual ~MainSkill();
};