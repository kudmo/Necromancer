#ifndef LAB3_IPOSISIONABLE_H
#define LAB3_IPOSISIONABLE_H

#include "../Dungeon/include/Field/Field.h"

class IPositionable {
    virtual const Floor& getFloor() const = 0;
    virtual void setFloor(Floor& floor) = 0;

    virtual const Field& getPosition() const = 0;
    virtual void setPosition(Field&) = 0;

};
#endif //LAB3_IPOSISIONABLE_H
