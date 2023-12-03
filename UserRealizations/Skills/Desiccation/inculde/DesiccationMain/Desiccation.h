#ifndef LAB3_DESICCATION_H
#define LAB3_DESICCATION_H


#include <string>
#include "MainSkill/MainSkill.h"

class Desiccation : public MainSkill {
public:
    void checkTarget(Object *) override;
    void checkUser(Entity *) override;
    void checkVariation(SubSkill *) override;
};


#endif //LAB3_DESICCATION_H
