#ifndef LAB3_CURSE_H
#define LAB3_CURSE_H

#include <string>
#include "../../../BaseInterfaces/Skill/include/MainSkill/MainSkill.h"
#include "../../Player/Player.h"

class Curse : public MainSkill {
private:
    uint price;
public:
    Curse(uint level): MainSkill(level) {}
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;
    void checkVariation(SubSkill *) override;
    std::string getName() override;
};

#endif //LAB3_CURSE_H
