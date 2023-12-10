#include <NecromancyVariations/NecromancyVariation.h>

void NecromancyVariation::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user("Only players can use it");
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));
}

void NecromancyVariation::checkTarget(Object *target) {
    auto p = dynamic_cast<DeadBody *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target("Target must be dead body");
}
