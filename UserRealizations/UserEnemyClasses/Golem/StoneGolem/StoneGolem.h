#ifndef LAB3_STONEGOLEM_H
#define LAB3_STONEGOLEM_H

#include "../../../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"

#include "../../../UserSpecialElements/Wall/Wall.h"
#include "../../../UserEnemyTypes/GolemType/StoneGolemType/StoneGolemType.h"

#include "../Golem.h"

class StoneGolem : public Golem {
public:
    StoneGolem(Floor& f, std::pair<size_t,size_t> coord, StoneGolemType* type, FRACTIONS fraction);
    void die() override;
};


#endif //LAB3_STONEGOLEM_H
