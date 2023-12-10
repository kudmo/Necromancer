#ifndef LAB3_SUBSKILL_H
#define LAB3_SUBSKILL_H

#include <string>


class Object;
class Entity;

class SubSkill {
public:
    SubSkill() = default;
    virtual uint getCost(uint level, const Object&) = 0;
    virtual std::string getName() = 0;
/*!
 * @throws skill_errors::invalid_skill_user if user can't use this skill
 */
    virtual void checkUser(Entity *) = 0;
/*!
 * @throws skill_errors::invalid_skill_target if this skill can't be used on this target
 */
    virtual void checkTarget(Object *) = 0;
    virtual void skill(uint level, Entity&, Object&) = 0;
    virtual ~SubSkill() = default;
};

#endif // LAB3_SUBSKILL_H