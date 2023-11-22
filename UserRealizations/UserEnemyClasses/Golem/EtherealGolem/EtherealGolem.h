#ifndef LAB3_ETHEREALGOLEM_H
#define LAB3_ETHEREALGOLEM_H


#include "../../../UserEnemyTypes/GolemType/EtherealGolemType/EtherealGolemType.h"

#include "../Golem.h"

class EtherealGolem : public Golem {
public:
    //!@todo Конструктор??
    EtherealGolem(Floor& f, std::pair<size_t,size_t> coord, EtherealGolemType* type, FRACTIONS fraction);
    uint getEssence() const;
    void die() override;
};
#endif //LAB3_ETHEREALGOLEM_H
