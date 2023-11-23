#ifndef LAB3_IMOVABLE_H
#define LAB3_IMOVABLE_H

#include <Field/Field.h>

enum class DIRECTIONS;

class IMovable {
    virtual void move() = 0;
    virtual void rotate(DIRECTIONS) = 0;
    virtual void stay() = 0;
};

#endif //LAB3_IMOVABLE_H
