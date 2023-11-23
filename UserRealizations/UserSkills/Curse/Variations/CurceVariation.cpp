#include "../../../../BaseInterfaces/Skill/include/Exeptions/SkillException.h"

#include "CurseVariation.h"

void CurseVariation::skill(Entity &user, Object &target) {
    try {
        Entity &p = dynamic_cast<Entity&>(target);
        p.damaged(user, damage);
    } catch (std::bad_cast& e) {
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
    }
}