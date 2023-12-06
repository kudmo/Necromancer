#include <DesiccationMain/Desiccation.h>
#include "DeadBody/DeadBody.h"
#include "Player/Player.h"
#include "DesiccationVariations/DesiccationVariation.h"

void Desiccation::checkTarget(Object *target) {
    auto p = dynamic_cast<DeadBody *>(target);
    if (p == nullptr) throw skill_errors::invalid_skill_target("Target must be dead body");
}

void Desiccation::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr) throw skill_errors::invalid_skill_user("Only players can use it");
}

void Desiccation::checkVariation(SubSkill *s) {
    auto sub = dynamic_cast<DesiccationVariation*>(s);
    if (sub == nullptr) {
        throw skill_errors::invalid_subskill_type_error(std::string("Only desiccation variations can be added as variations of desiccation"));
    }
}

const std::string Desiccation::getName() const noexcept {
    return "desiccation";
}

MainSkill *DesiccationBuilder::build(uint level) const {
    return new Desiccation(level);
}
