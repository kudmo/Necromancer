#include <MorphismMain/Morphism.h>
#include "Player/Player.h"
#include "MorphismVariations/MorphismVariation.h"

void Morphism::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user(std::string("Only players can use it"));
}

void Morphism::checkVariation(SubSkill *s) {
    auto sub = dynamic_cast<MorphismVariation*>(s);
    if (sub == nullptr)
        throw skill_errors::invalid_subskill_type_error(std::string("Only morphism variations can be added as variations of morphism"));
}

void Morphism::checkTarget(Object *target) {
    auto p = dynamic_cast<Undead *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
}

const std::string Morphism::getName() const noexcept {
    return "morphism";
}

std::unique_ptr<MainSkill> MorphismBuilder::build(uint level) const {
    return std::make_unique<Morphism>(level);
}
