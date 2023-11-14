#include <string>

#include "../../../BaseInterfaces/Skill/include/Exeptions/SkillException.h"
#include "../../Player/Player.h"
#include "Necromancy.h"
#include "NecromancyVariation.h"
#include "../../UserItems/DeadBody/DeadBody.h"

void Necromancy::checkVariation(SubSkill *s) {
    auto sub = dynamic_cast<NecromancyVariation*>(s);
    if (sub == nullptr) {
        throw invalid_subskill_type_error(std::string("Only necromancy variations can be added as variations of necromancy"));
    }

}

void Necromancy::checkUser(Entity *user) {
    auto p = dynamic_cast<Player *>(user);
    if (p == nullptr) throw invalid_skill_user("Only players can use it");
}

void Necromancy::checkTarget(Object *target) {
    auto p = dynamic_cast<DeadBody *>(target);
    if (p == nullptr) throw invalid_skill_target("Target must be dead body");
}

std::string Necromancy::getName() {
    return std::string("Necromancy");
}