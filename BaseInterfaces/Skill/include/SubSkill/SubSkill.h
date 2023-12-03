#ifndef LAB3_SUBSKILL_H
#define LAB3_SUBSKILL_H

#include <string>


class Object;
class Entity;

class SubSkill {
public:
    SubSkill() = default;
    virtual uint getCost(uint level) = 0;
    virtual std::string getName() = 0;
    virtual void skill(uint level, Entity&, Object&) = 0;
    virtual ~SubSkill() = default;
};

#endif // LAB3_SUBSKILL_H