#ifndef LAB3_IPOSISIONABLE_H
#define LAB3_IPOSISIONABLE_H

#include "../Dungeon/include/Field/Field.h"

class IPositionable {
    virtual Field* getPosition() = 0;
    virtual void setPosition(Field*) = 0;

};
#endif //LAB3_IPOSISIONABLE_H
