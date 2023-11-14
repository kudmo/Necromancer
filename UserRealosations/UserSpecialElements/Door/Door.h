#ifndef LAB3_DOOR_H
#define LAB3_DOOR_H

#include <utility>
#include "../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"

class Door : public SpecialElement {
private:
    bool opened = false;
public:
    Door() = default;
    bool isPassable() override {
        return opened;
    }
    void interact(ISmartInteractor &e) override {
        opened = !opened;
    }
    ~Door();
};


#endif //LAB3_DOOR_H
