#ifndef LAB3_ETHEREALGOLEM_H
#define LAB3_ETHEREALGOLEM_H

#include "../Golem.h"
#include "../../../UserEnemyTypes/GolemType/EtherealGolemType/EtherealGolemType.h"

class EtherealGolem : public Golem {
public:
    //!@todo Конструктор??
    uint getEssence() const {
        auto t = dynamic_cast<EtherealGolemType*>(type);
        return t->getEssenceCount();
    }
    void die() override {
        this->getPosition().addEssence(this->getEssence());
        Golem::die();
    }
    ~EtherealGolem();
};
#endif //LAB3_ETHEREALGOLEM_H
