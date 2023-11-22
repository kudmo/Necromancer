#ifndef LAB3_MORPHISM_H
#define LAB3_MORPHISM_H

#include <string>
#include "../../../BaseInterfaces/Skill/include/MainSkill/MainSkill.h"

class Morphism : public MainSkill {
public:
    void checkVariation(SubSkill *) override;
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;
};


#endif //LAB3_MORPHISM_H
