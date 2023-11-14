#ifndef LAB3_FIREGOLEM_H
#define LAB3_FIREGOLEM_H

#include "../Golem.h"
#include "../../../UserCoverages/Magma/Magma.h"

class FireGolem : public Golem {
public:
    //!@todo Конструктор??
    void die() override {
        auto magma = new Magma();
        this->getPosition().setCoverage(magma);
        Golem::die();
    }
    virtual ~FireGolem();
};
#endif //LAB3_FIREGOLEM_H
