#ifndef LAB3_NECROMANCYSKELETON_H
#define LAB3_NECROMANCYSKELETON_H

#include <string>

#include "../NecromancyVariation.h"
#include "../../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../UserEnemyClasses/Undead/UndeadBuilder.h"

#include "../../../../BaseInterfaces/Skill/include/Exeptions/SkillException.h"
#include "../../../UserItems/DeadBody/DeadBody.h"
#include "../../../Player/Player.h"

template <typename T>// requires std::is_same<T, UndeadType>
class NecromancyAs : public NecromancyVariation {
private:
    uint level = 1;
    typedef T type_of_resurrected_undead ;
public:
    void skill(Entity& user, Object& target) override {
        try {
            dynamic_cast<DeadBody &>(target);
        } catch (std::bad_cast& e) {
            throw skill_errors::invalid_skill_target("Necromancy can only be used on dead bodies");
        }

        try {
            dynamic_cast<Player &>(user);
        } catch (std::bad_cast& e) {
            throw skill_errors::invalid_skill_user("Only players can use necromancy");
        }

        Player &p = dynamic_cast<Player &>(user);
        DeadBody &body = dynamic_cast<DeadBody &>(target);
        UndeadBuilder<type_of_resurrected_undead> builder;
        auto type = body.takeBody();

        Undead& summoned = builder.CreateUndead(body.getFloor(), body.getCoordinates(), body.getType().getLevel(), type, user.getFraction());
        p.addNewControlledUndead(summoned);
        //! @todo удаление тела
        body.getPosition().removeItem(body);
    }
};

#endif //LAB3_NECROMANCYSKELETON_H
