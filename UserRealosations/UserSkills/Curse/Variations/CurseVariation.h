#ifndef LAB3_CURSEVARIATION_H
#define LAB3_CURSEVARIATION_H

#include "../../../../BaseInterfaces/Skill/include/Exeptions/SkillException.h"
#include "../../../../BaseInterfaces/Skill/include/SubSkill/SubSkill.h"

class CurseVariation : public SubSkill {
private:
    uint damage = 10;
public:
    void skill(Entity &user, Object &target) override {
        Entity *p = dynamic_cast<Entity *>(&target);
        if (p == nullptr) throw invalid_skill_target(std::string("Target must be entity"));
        p->damaged(user, damage);
    }
};
#endif //LAB3_CURSEVARIATION_H
