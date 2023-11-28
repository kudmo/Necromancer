#pragma once

#include <string>


class Object;
class Entity;

class SubSkill {
private:
    uint level = 1;
public:
    SubSkill() = default;
    explicit SubSkill(uint level);
    //! @todo Подумать о том, нужен ли этот метод (нужен)
    virtual void Upgrade() = 0;
    virtual uint getCost() = 0;
    uint getLevel() const;
    void setLevel(uint level);
    virtual std::string getName() = 0;
    virtual void skill(Entity&, Object&) = 0;
    virtual ~SubSkill() = default;
};