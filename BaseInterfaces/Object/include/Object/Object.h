#ifndef LAB3_OBJECT_H
#define LAB3_OBJECT_H

#include <utility>

#include "../../../Interfaces/IPosisionable.h"

#include <Floor/Floor.h>
#include <Field/Field.h>

class Floor;
class Field;

class Object : public IPositionable {
private:
    //! @todo Возможно тут лучше weak_ptr
    Floor *floor;
    std::pair<size_t,size_t> coord;
public:
    Object(Floor& f, std::pair<size_t,size_t> coord): floor(&f), coord(coord) {}

    Floor & getFloor() override;
    const Floor & getFloor() const override;

    void setFloor(Floor& floor) override;

    Field & getPosition() override;
    const Field& getPosition() const override;

    std::pair<size_t, size_t> getCoordinates() const override;
    void setCoordinates(std::pair<size_t, size_t> coordinates) override;

    virtual ~Object() = default;
};

#endif //LAB3_OBJECT_H