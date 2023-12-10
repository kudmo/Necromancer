#include <CurseVariations/CurseVariation.h>

#include <Entity/Entity.h>
#include <Object/Object.h>

#include <Exceptions/SkillExceptions.h>
#include "Player/Player.h"

void CurseVariation::skill(uint level, Entity &user, Object &target) {
    checkUser(&user);
    checkTarget(&target);

    auto &p = dynamic_cast<Entity&>(target);
    p.damaged(user, calculateDamage(level));
}

void CurseVariation::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user(std::string("Only players can use it"));
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));
}

void CurseVariation::checkTarget(Object *target) {
    auto p = dynamic_cast<Entity *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));
}

std::unique_ptr<SubSkill> CurseVariationBuilder::build() const {
    return std::make_unique<CurseVariation>();
}
