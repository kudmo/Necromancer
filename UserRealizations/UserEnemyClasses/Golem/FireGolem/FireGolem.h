#ifndef LAB3_FIREGOLEM_H
#define LAB3_FIREGOLEM_H

#include "../../../UserCoverages/Magma/Magma.h"
#include "../../../UserEnemyTypes/GolemType/FireGolemType/FireGolemType.h"

#include "../Golem.h"

class FireGolem : public Golem {
public:
    FireGolem(Floor& f, std::pair<size_t,size_t> coord, FireGolemType* type, FRACTIONS fraction);
    void die() override;
};
#endif //LAB3_FIREGOLEM_H
