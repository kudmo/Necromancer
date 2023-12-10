#include <DesiccationVariations/DesiccationVariation.h>
#include "Player/Player.h"
#include "DeadBody/DeadBody.h"

void DesiccationVariation::checkUser(Entity *user) {

    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr)
        throw skill_errors::invalid_skill_user("Only players can use it");
    else if (p->isDead())
        throw entity_errors::already_dead_exception(std::string("Dead can't"));

}

void DesiccationVariation::checkTarget(Object *target) {
    auto p = dynamic_cast<DeadBody *>(target);
    if (p == nullptr)
        throw skill_errors::invalid_skill_target("Target must be dead body");
}


void DesiccationVariationMana::skill(uint level, Entity &user, Object &target) {
    checkUser(&user);
    checkTarget(&target);

    auto& p = dynamic_cast<Player&>(user);
    auto& body = dynamic_cast<DeadBody&>(target);

    p.restoreMP(calculateProfit(level, body.getType()));
    body.getPosition().removeItem(body);
}

uint DesiccationVariationMana::calculateProfit(uint level, const EnemyType &o) const {
    return o.getMaxHp() * 10* 0.5 * level;
}

std::string DesiccationVariationMana::getName() {
    return "desiccation_mana";
}






void DesiccationVariationHealth::skill(uint level, Entity &user, Object &target) {
    checkUser(&user);
    checkTarget(&target);

    auto& p = dynamic_cast<Player&>(user);
    auto& body = dynamic_cast<DeadBody&>(target);

    p.restoreHP(calculateProfit(level, body.getType()));
    body.getPosition().removeItem(body);
}


uint DesiccationVariationHealth::calculateProfit(uint level, const EnemyType &o) const {
    return o.getMaxHp() * 10* 0.5 * level;;
}

std::string DesiccationVariationHealth::getName() {
    return "desiccation_health";
}


std::unique_ptr<SubSkill> DesiccationVariationManaBuilder::build() const {
    return std::make_unique<DesiccationVariationMana>();
}

std::unique_ptr<SubSkill> DesiccationVariationHealthBuilder::build() const {
    return std::make_unique<DesiccationVariationHealth>();
}
