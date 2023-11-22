#ifndef LAB3_SPECIALELEMENT_H
#define LAB3_SPECIALELEMENT_H

#include "../Field/Field.h"

class Field;

class ISmartInteractor {
public:
    virtual void smartInteract(Field&) = 0;
};

class SpecialElement {
public:
    virtual bool isPassable() = 0;
    virtual void interact(ISmartInteractor&) = 0;
    virtual ~SpecialElement() = default;
};


#endif //LAB3_SPECIALELEMENT_H
