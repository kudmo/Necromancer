#ifndef LAB3_IPOSISIONABLE_H
#define LAB3_IPOSISIONABLE_H

#include <utility>

#include <Floor/Floor.h>
#include <Field/Field.h>

class Field;
class Floor;

class IPositionable {
    virtual Floor& getFloor() = 0;
    virtual const Floor& getFloor() const = 0;
    virtual void setFloor(Floor& floor) = 0;

    virtual std::pair<size_t, size_t> getCoordinates() const = 0;
    virtual void setCoordinates(std::pair<size_t, size_t>) = 0;

    virtual Field& getPosition() = 0;
    virtual const Field& getPosition() const = 0;
};
#endif //LAB3_IPOSISIONABLE_H
