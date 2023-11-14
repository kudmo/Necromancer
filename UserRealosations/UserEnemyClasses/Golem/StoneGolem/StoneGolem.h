#ifndef LAB3_STONEGOLEM_H
#define LAB3_STONEGOLEM_H

#include "../Golem.h"
#include "../../../UserSpecialElements/Wall/Wall.h"
#include "../../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"

class StoneGolem : public Golem {
public:
    //!@todo Конструктор??

    void die() override {
        auto wall = new Wall();
        this->getPosition().setSpecialization(wall);
        Golem::die();
    }
};


#endif //LAB3_STONEGOLEM_H
