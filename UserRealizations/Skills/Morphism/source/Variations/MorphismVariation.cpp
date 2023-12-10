#include <MorphismVariations/MorphismVariation.h>

void MorphismVariation::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user(std::string("Only players can use it"));
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));
}

void MorphismVariation::checkTarget(Object *target) {
    auto p = dynamic_cast<Undead *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));

}