#ifndef LAB3_CURSEVARIATION_H
#define LAB3_CURSEVARIATION_H

#include "../../../../BaseInterfaces/Skill/include/Exeptions/SkillException.h"
#include "../../../../BaseInterfaces/Skill/include/SubSkill/SubSkill.h"

class CurseVariation : public SubSkill {
private:
    uint damage = 10;
public:
    /*!
     * @throws skill_errors::invalid_skill_target if Target isn't entity
     */
    void skill(Entity &user, Object &target) override;
};
#endif //LAB3_CURSEVARIATION_H
