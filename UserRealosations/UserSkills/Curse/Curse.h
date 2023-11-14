#ifndef LAB3_CURSE_H
#define LAB3_CURSE_H

#include <string>
#include "../../../BaseInterfaces/Skill/include/MainSkill/MainSkill.h"

class Curse : public MainSkill {
private:
    uint price;
public:
    Curse(uint level, SubSkill& def): MainSkill(level, def) {};
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;
    void checkVariation(SubSkill *) override;
    std::string getName() override;
};

#endif //LAB3_CURSE_H
