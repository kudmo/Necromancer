#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H

#include <utility>
#include <vector>
#include <string>

#include "../../BaseInterfaces/Entity/include/Entity/Entity.h"
#include "../../BaseInterfaces/Dungeon/include/Dungeon/Dungeon.h"
#include "../../BaseInterfaces/Dungeon/include/SpecialElement/SpecialElement.h"
#include "../../BaseInterfaces/Skill/include/SkillTable/SkillTable.h"
#include "../../BaseInterfaces/Interfaces/IExperienceCollector.h"
#include "../../BaseInterfaces/Interfaces/IAttacker.h"

#include "../UserEnemyClasses/Undead/Undead.h"

class Player : public Entity, public IUpdatable, public ISmartInteractor, public IExperienceCollector {
private:
    uint level;
    uint experience;
    uint skill_points;
    uint essence_count;
    uint max_hp;
    uint current_hp;
    uint damage;
    uint max_mana_count;
    uint current_mana_count;
    uint max_undead_count;
    std::vector<std::weak_ptr<Undead>> controlled_undead;
    SkillTable skills;
    uint needExpToUpgrade() const;
public:
    //! @todo Конструктор
    Player(): Entity(FRACTIONS::PLAYER);
    uint damaged(IAttacker&, uint) override;

    void die() override;

    uint getDamage() const override {
        return damage;
    }
    uint getMaxHp() const override {
        return max_hp;
    }
    uint getCurrentHp() const override {
        return current_hp;
    }

    void smartInteract(Field& f) override {
        f.specialInteract(*this);
    }
    void interactWithCurrentField() override;
    void interactWithNextField() override;

    void collectExperience(uint) override;
    void collectEssence(uint);
    void upgradeLevel();

    void useSkill(std::string, Object&);

    //! @todo нужны глобальные объекты для таблицы навыков
    void exploreNewUndeadType(std::string);
    void upgradeSkill(std::string);
};

#endif //LAB3_PLAYER_H
