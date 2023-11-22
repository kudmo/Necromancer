#pragma once

#include <utility>

#include "../../../Interfaces/IPosisionable.h"

#include "../../../Dungeon/include/Field/Field.h"

#include "../../../Dungeon/include/Exceptions/DungeonExceptions.h"

class Object : public IPositionable {
private:
    //! @todo Возможно тут лучше weak_ptr
    Floor *floor;
    std::pair<size_t,size_t> coord;
public:
    Object(Floor& f, std::pair<size_t,size_t> coord): floor(&f), coord(coord) {}

    Floor & getFloor() override {
        return *floor;
    }
    const Floor & getFloor() const override {
        return *floor;
    }

    void setFloor(Floor& floor) override {
        this->floor = &floor;
    }

    Field & getPosition() override {
        return floor->getByCoord(coord);
    }
    const Field& getPosition() const override {
        return floor->getByCoord(coord);
    }

    std::pair<size_t, size_t> getCoordinates() const override {
        return coord;
    }

    void setCoordinates(std::pair<size_t, size_t> coordinates) override {
        this->coord = coordinates;
    }

    virtual ~Object() = default;
};