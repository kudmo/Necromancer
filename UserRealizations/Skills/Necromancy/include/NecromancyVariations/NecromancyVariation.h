#ifndef LAB3_NECROMANCYVARIATION_H
#define LAB3_NECROMANCYVARIATION_H

#include <SubSkill/SubSkill.h>

#include <Undead/Undead.h>
#include <UndeadType/UndeadType.h>

#include <DeadBody/DeadBody.h>
#include <Player/Player.h>

#include <Exceptions/SkillExceptions.h>


class NecromancyVariation : public SubSkill {};

template <typename T> requires std::is_base_of_v<UndeadType, T>
class NecromancyAs : public NecromancyVariation {
private:
    uint level = 1;
    typedef T type_of_resurrected_undead ;
public:
    void skill(Entity& user, Object& target) override {
        try {
            dynamic_cast<DeadBody&>(target);
        } catch (std::bad_cast& e) {
            throw skill_errors::invalid_skill_target("Necromancy can only be used on dead bodies");
        }

        try {
            dynamic_cast<Player&>(user);
        } catch (std::bad_cast& e) {
            throw skill_errors::invalid_skill_user("Only players can use necromancy");
        }

        auto &p = dynamic_cast<Player &>(user);
        auto &body = dynamic_cast<DeadBody &>(target);
        UndeadBuilderAs<type_of_resurrected_undead> builder;

        auto type = body.takeBody();

        Enemy& summoned = builder.build(body.getFloor(), body.getCoordinates(), type->getLevel(), *type, user.getFraction());
        p.addNewControlledUndead(dynamic_cast<Undead&>(summoned));
        //! @todo удаление тела
        body.getPosition().removeItem(body);
    }
    uint getCost() override {return 1;}
    void Upgrade() override {setLevel(getLevel()+1);}
    std::string getName() override {return std::string("Necromancy");}
};

#endif //LAB3_NECROMANCYVARIATION_H
