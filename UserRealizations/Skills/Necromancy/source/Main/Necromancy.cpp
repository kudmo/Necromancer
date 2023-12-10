#include <string>

#include <Exceptions/SkillExceptions.h>
#include "Player/Player.h"
#include <NecromancyMain/Necromancy.h>
#include <NecromancyVariations/NecromancyVariation.h>
#include <DeadBody/DeadBody.h>

void Necromancy::checkVariation(SubSkill *s) {
    auto sub = dynamic_cast<NecromancyVariation*>(s);
    if (sub == nullptr) {
        throw skill_errors::invalid_subskill_type_error(std::string("Only necromancy variations can be added as variations of necromancy"));
    }
}

void Necromancy::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user("Only players can use it");
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));

}

void Necromancy::checkTarget(Object *target) {
    auto p = dynamic_cast<DeadBody *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target("Target must be dead body");
}

const std::string Necromancy::getName() const noexcept {
    return std::string("necromancy");
}

std::unique_ptr<MainSkill> NecromancyBuilder::build(uint level) const {
    return std::make_unique<Necromancy>(level);
}
