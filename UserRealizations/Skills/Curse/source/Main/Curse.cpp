#include <CurseMain/Curse.h>
#include <CurseVariations/CurseVariation.h>
#include <Object/Object.h>
#include <Entity/Entity.h>
#include <Player/Player.h>

void Curse::checkVariation(SubSkill *s) {
    auto sub = dynamic_cast<CurseVariation*>(s);
    if (sub == nullptr)
        throw skill_errors::invalid_subskill_type_error(std::string("Only curse variations can be added as variations of curse"));
}

void Curse::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user(std::string("Only players can use it"));
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));

}

void Curse::checkTarget(Object *target) {
    auto p = dynamic_cast<Entity *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target(std::string("Target must be entity"));
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));

}

const std::string Curse::getName() const noexcept {
    return std::string("curse");
}

std::unique_ptr<MainSkill> CurseBuilder::build(uint level) const {
    return std::make_unique<Curse>(level);
}

