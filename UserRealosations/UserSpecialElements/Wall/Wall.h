#ifndef LAB3_WALL_H
#define LAB3_WALL_H

#include "../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"

class Wall : public SpecialElement {
public:
    Wall() = default;;
    bool isPassable() override {return false;}
    void interact(ISmartInteractor &) override {
        //! @todo Сделать или "ударяться головой" или исключение;
    }
    ~Wall();
};


#endif //LAB3_WALL_H
