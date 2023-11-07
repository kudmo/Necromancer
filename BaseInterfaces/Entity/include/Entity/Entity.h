#ifndef LAB3_ENTITY_H
#define LAB3_ENTITY_H

#include <cstdlib>
#include <utility>

#include "../../../Object/include/Object/Object.h"
#include "../../../Interfaces/IAttackable.h"
#include "../../../Interfaces/IMovable.h"

enum class FRACTIONS {

};

class Entity : public Object, public IAttackable, public IMovable{
public:
    void move() override;
    void rotate(DIRECTIONS) override;
    void stay() override;

    virtual FRACTIONS getFraction() const;

    virtual uint getMaxHp() const;
    virtual uint getCurrentHp() const;
    virtual uint getDamage() const;

    virtual void interactWithCurrentField();
    virtual void interactWithNextField();

    virtual void attack(IAttackable&);
    uint damaged(uint) override;

    virtual void die() = 0;
};

#endif //LAB3_ENTITY_H
