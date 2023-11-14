#ifndef LAB3_LADDER_H
#define LAB3_LADDER_H

#include "../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"
#include "../../../BaseInterfaces/Dungeon/include/Floor/Floor.h"

class Ladder : public SpecialElement{
private:
    //!@todo возможно лучше хранить просто номер уровня
    Floor *purpose;
    Floor &current;
public:
    Ladder(Floor &current, Floor &purpose): current(current) {
        this->purpose = &purpose;
    }
    bool isPassable() override {
        return true;
    }

    void interact(ISmartInteractor& e) override {
        //! @todo Вопросы к тому, а не очистится ли объект совсем)
        current.removeEntity(dynamic_cast<Entity&>(e));
        purpose->loadFloor();
        purpose->addEntity(dynamic_cast<Entity&>(e));
    }
    ~Ladder();
};


#endif //LAB3_LADDER_H
