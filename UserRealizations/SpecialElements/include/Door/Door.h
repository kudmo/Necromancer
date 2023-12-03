#ifndef LAB3_DOOR_H
#define LAB3_DOOR_H

#include <utility>
#include "SpecialElement/SpecialElement.h"
#include "SpecialElement/SpecialElementBuilder.h"

class Door : public SpecialElement {
private:
    bool opened = false;
public:
    Door() = default;

    std::string getInfo() override;

    bool isPassable() override;
    void interact(ISmartInteractor &e) override;
};



#endif //LAB3_DOOR_H
