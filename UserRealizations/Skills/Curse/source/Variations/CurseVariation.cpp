#include <CurseVariations/CurseVariation.h>

#include <Entity/Entity.h>
#include <Object/Object.h>

#include <Exceptions/SkillExceptions.h>

void CurseVariation::skill(uint level, Entity &user, Object &target) {
    try {
        Entity &p = dynamic_cast<Entity&>(target);
        p.damaged(user, calculateDamage(level));
    } catch (std::bad_cast& e) {
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
    }
}

SubSkill *CurseVariationBuilder::build() const {
    return new CurseVariation();
}
