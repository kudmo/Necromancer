#ifndef LAB3_ENTITY_H
#define LAB3_ENTITY_H

#include <cstdlib>
#include <utility>

#include "../../../Object/include/Object/Object.h"
#include "../../../Interfaces/IAttackable.h"
#include "../../../Interfaces/IAttacker.h"
#include "../../../Interfaces/IMovable.h"

enum class FRACTIONS {
    ENEMY,
    PLAYER,
 //! @todo Фракции прописать
};

class Entity : public Object, public IAttackable, public IAttacker, public IMovable {
private:
    DIRECTIONS direction;
    FRACTIONS fraction;
public:
    Entity(FRACTIONS f): fraction(f) {};
    void move() override {
        Field* next = this->getFloor().getNextByDirection(*this->getPosition(), direction);
        if (!next || !next.isPassable())
            throw NO; //!@todo нормаьное искючение

        this->setPosition(next);
        this->getPosition().whenEntrance(*this);
    }
    void rotate(DIRECTIONS dir) override {
        direction = dir;
    }
    void stay() override {
        this->getPosition().whenStay(*this);
    }

    const DIRECTIONS getDirection() const {
        return direction;
    }
    const FRACTIONS getFraction() const {
        return fraction;
    }

    virtual uint getMaxHp() const;
    virtual uint getCurrentHp() const;
    virtual uint getDamage() const;

    //! @todo А нужны ли эти 2 метода?
    virtual void interactWithCurrentField();
    virtual void interactWithNextField();

    void attack(IAttackable& target) override {
        target.damaged(*this, getDamage());
    }

    virtual void die() {
        //! @todo Удаление сущности из уровня
        this->getFloor().removeEntity(*this);
        //! @todo Очистка памяти?
    }

    virtual ~Entity() = default;
};

#endif //LAB3_ENTITY_H
