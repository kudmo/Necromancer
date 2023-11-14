#ifndef LAB3_NECROMANCYSKELETON_H
#define LAB3_NECROMANCYSKELETON_H

#include <string>

#include "../NecromancyVariation.h"
#include "../../../UserEnemyTypes/UndeadType/UndeadType.h"
#include "../../../UserEnemyClasses/Undead/UndeadBuilder.h"

#include "../../../../BaseInterfaces/Skill/include/Exeptions/SkillException.h"
#include "../../../UserItems/DeadBody/DeadBody.h"

template <T> requires std::is_same<T, UndeadType>
class NecromancyAs : public NecromancyVariation {
private:
    uint level = 1;
    typedef T type_of_resurrected_undead;
    type_of_resurrected_undead copy = ;
public:
    void skill(Entity& user, Object& target) override {
        try {
            auto body = dynamic_cast<DeadBody &>(target);
            UndeadBuilder<type_of_resurrected_undead> builder;
            auto type = body.takeType();
            //! @todo удаление из клетки

            auto summoned = builder.CreateUndead(body.getLevel(), type);
            summoned->setPosition(body.getPosition());
            //! @todo удаление тела
            delete &body;
        } catch (std::bad_cast) {
            throw invalid_skill_target("Necromancy can only be used on dead bodies");
        }

    }
    std::string getName() override {
        return
    }
};

#endif //LAB3_NECROMANCYSKELETON_H
