#ifndef LAB3_MORPHISMVARIATION_H
#define LAB3_MORPHISMVARIATION_H

#include <SubSkill/SubSkill.h>
#include <SubSkill/SubSkillBuilder.h>

#include <Exceptions/SkillExceptions.h>
#include "UndeadType/UndeadType.h"
#include "Undead/Undead.h"
#include "Player/Player.h"

#include <iostream>

class MorphismVariation : public SubSkill {
public:
    void checkUser(Entity *entity) override;

    void checkTarget(Object *object) override;
};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class MorphismAs : public MorphismVariation {
public:
    void skill(uint level, Entity &user, Object &target) override {
        checkUser(&user);
        checkTarget(&target);

        auto &p = dynamic_cast<Player&>(user);
        auto &undead = dynamic_cast<Undead&>(target);
        if (typeid(undead.getBody()) == typeid(T)) // ибо нефиг
            return;

        auto coord = undead.getCoordinates();
        auto &floor = undead.getFloor();
        auto frac = undead.getFraction();
        auto undead_level = undead.getLevel();

        auto type = undead.takeInnerBody();
        auto alive_t = type->takeInnerBody();
        auto &new_undead = UndeadBuilderAs<T>().build(floor, coord, undead_level, std::move(alive_t), frac);
    }
    std::string getName() override;
    uint getCost(uint level, const Object&) override;
};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class MorphismAsBuilder : public SubSkillBuilder {
public:
    std::unique_ptr<SubSkill> build() const override {
        return std::make_unique<MorphismAs<T>>();
    }
};
#endif //LAB3_MORPHISMVARIATION_H
