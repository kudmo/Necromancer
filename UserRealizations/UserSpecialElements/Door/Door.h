#ifndef LAB3_DOOR_H
#define LAB3_DOOR_H

#include <utility>
#include "../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"

class Door : public SpecialElement {
private:
    bool opened = false;
public:
    Door() = default;
    bool isPassable() override;
    void interact(ISmartInteractor &e) override;
};


#endif //LAB3_DOOR_H
