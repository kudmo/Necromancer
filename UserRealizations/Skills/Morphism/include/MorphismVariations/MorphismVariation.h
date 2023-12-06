#ifndef LAB3_MORPHISMVARIATION_H
#define LAB3_MORPHISMVARIATION_H

#include <SubSkill/SubSkill.h>
#include <SubSkill/SubSkillBuilder.h>

#include <Exceptions/SkillExceptions.h>
#include "UndeadType/UndeadType.h"
#include "Undead/Undead.h"
#include "Player/Player.h"

#include <iostream>

class MorphismVariation : public SubSkill {};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class MorphismAs : public MorphismVariation {
public:
    void skill(uint level, Entity &user, Object &target) override {
        try {
            dynamic_cast<Undead&>(target);
        } catch (std::bad_cast& e) {
            throw skill_errors::invalid_skill_target("Necromancy can only be used on dead bodies");
        }

        try {
            dynamic_cast<Player&>(user);
        } catch (std::bad_cast& e) {
            throw skill_errors::invalid_skill_user("Only players can use necromancy");
        }
        auto &p = dynamic_cast<Player&>(user);
        auto &undead = dynamic_cast<Undead&>(target);
        if (typeid(undead.getBody()) == typeid(T)) // ибо нефиг
            return;

        auto coord = undead.getCoordinates();
        auto &floor = undead.getFloor();
        auto frac = undead.getFraction();
        auto undead_level = undead.getLevel();

        auto *type = undead.takeInnerBody();
        auto *alive_t = type->takeInnerBody();
        auto &new_undead = UndeadBuilderAs<T>().build(floor, coord, undead_level, *alive_t, frac);
        delete type;
    }
    std::string getName() override;
    uint getCost(uint level, const Object&) override;
};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class MorphismAsBuilder : public SubSkillBuilder {
public:
    SubSkill *build() const override {
        return new MorphismAs<T>();
    }
};
#endif //LAB3_MORPHISMVARIATION_H
