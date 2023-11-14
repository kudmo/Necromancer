#pragma once

#include "../../../Interfaces/IPosisionable.h"
#include "../../../Dungeon/include/Field/Field.h"

class Object : public IPositionable {
private:
    Floor *floor;
    //! @todo возможно просто лучше хранить координаты
    Field *position;
public:
    Floor & getFloor() const override {
        return *floor;
    }
    void setFloor(Floor& floor) override {
        this->floor = &floor;
    }

    Field& getPosition() const override {
        return *position;
    }
    void setPosition(Field &position) override {
        this->position = &position;
    }

    virtual ~Object() = default;
};