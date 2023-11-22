#ifndef LAB3_LADDER_H
#define LAB3_LADDER_H

#include "../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"
#include "../../../BaseInterfaces/Dungeon/include/Floor/Floor.h"

class Ladder : public SpecialElement{
private:
    //!@todo возможно лучше хранить просто номер уровня
    size_t from;
    size_t to;
    Dungeon& dungeon;
public:
    Ladder(Dungeon& d, size_t from, size_t to);
    bool isPassable() override;
    void interact(ISmartInteractor& e) override;
};


#endif //LAB3_LADDER_H
