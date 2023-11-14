#ifndef LAB3_NECROMANCY_H
#define LAB3_NECROMANCY_H

#include <string>
#include "../../../BaseInterfaces/Skill/include/MainSkill/MainSkill.h"

class Necromancy : public MainSkill{
private:
    uint price;
public:
    Necromancy(uint level);
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;
    void checkVariation(SubSkill *) override;
    std::string getName() override;
};

#endif //LAB3_NECROMANCY_H
