#include "Curse.h"
#include "Variations/CurseVariation.h"

void Curse::checkVariation(SubSkill *s) {
    auto sub = dynamic_cast<CurseVariation*>(s);
    if (sub == nullptr)
        throw skill_errors::invalid_subskill_type_error(std::string("Only curse variations can be added as variations of curse"));
}

void Curse::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user(std::string("Only players can use it"));
}

void Curse::checkTarget(Object *target) {
    auto p = dynamic_cast<Entity *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
}

std::string Curse::getName() {
    return std::string("Curse");
}