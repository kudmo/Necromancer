#ifndef LAB3_WALL_H
#define LAB3_WALL_H

#include "SpecialElement/SpecialElement.h"

class Wall : public SpecialElement {
public:
    Wall() = default;
    bool isPassable() override;
    void interact(ISmartInteractor &) override;
};


#endif //LAB3_WALL_H
