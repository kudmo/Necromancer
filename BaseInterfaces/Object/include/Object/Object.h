#pragma once

#include "../../../Interfaces/IPosisionable.h"
#include "../../../Dungeon/include/Field/Field.h"

class Object : public IPositionable{
private:
    Field *position;
public:
    Field * getPosition() override;
    void setPosition(Field *) override;
};