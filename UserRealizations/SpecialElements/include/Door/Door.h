#ifndef LAB3_DOOR_H
#define LAB3_DOOR_H

#include <utility>
#include "SpecialElement/SpecialElement.h"

class Door : public SpecialElement {
private:
    bool opened = false;
public:
    Door() = default;
    bool isPassable() override;
    void interact(ISmartInteractor &e) override;
};

class DoorBuilder : public SpecialElementBuilder {
public:
    SpecialElement * build() override;
};

#endif //LAB3_DOOR_H
