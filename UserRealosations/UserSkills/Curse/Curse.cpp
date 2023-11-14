#include "Curse.h"


void Curse::checkVariation(SubSkill *s) {
    throw invalid_subskill_type_error(std::string("There are no nodefault variation fo curse "));
}

void Curse::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr) throw invalid_skill_user(std::string("Only players can use it"));
}

void Curse::checkTarget(Object *target) {
    auto p = dynamic_cast<Entity *>(target);
    if (p == nullptr) throw invalid_skill_target(std::string("Target must be entity"));
}

std::string Curse::getName() {
    return std::string("Curse");
}