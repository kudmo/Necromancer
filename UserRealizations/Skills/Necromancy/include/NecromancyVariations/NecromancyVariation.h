#ifndef LAB3_NECROMANCYVARIATION_H
#define LAB3_NECROMANCYVARIATION_H

#include <SubSkill/SubSkill.h>
#include <SubSkill/SubSkillBuilder.h>
#include <Undead/Undead.h>
#include <UndeadType/UndeadType.h>

#include <DeadBody/DeadBody.h>
#include <Player/Player.h>

#include <Exceptions/SkillExceptions.h>


class NecromancyVariation : public SubSkill {
public:
    void checkUser(Entity *entity) override;
    void checkTarget(Object *object) override;
};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class NecromancyAs : public NecromancyVariation {
private:
    uint level = 1;
    typedef T type_of_resurrected_undead ;
public:
    void skill(uint level, Entity& user, Object& target) override {
        checkUser(&user);
        checkTarget(&target);

        auto &p = dynamic_cast<Player &>(user);
        auto &body = dynamic_cast<DeadBody &>(target);
        UndeadBuilderAs<type_of_resurrected_undead> builder;

        auto type = body.takeBody();
        auto &f = body.getFloor();
        Enemy& summoned = builder.build(f.getDungeon(), f.getFloorNumber(), body.getCoordinates(), type->getLevel(), std::move(type), user.getFraction());
        p.addNewControlledUndead(dynamic_cast<Undead&>(summoned));
        body.getPosition().removeItem(body);
    }
    uint getCost(uint level, const Object&) override {return 50-5*level;}
    std::string getName() override;
};

class NecromancyVariationBuilder : public SubSkillBuilder {};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class NecromancyAsBuilder : public NecromancyVariationBuilder {
public:
    std::unique_ptr<SubSkill> build() const override {
        return std::make_unique<NecromancyAs<T>>();
    }
};
#endif //LAB3_NECROMANCYVARIATION_H
