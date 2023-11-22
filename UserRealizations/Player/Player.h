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
#include "Exceptions.h"

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
//    std::vector<std::weak_ptr<Undead>> controlled_undead;
    uint current_undead_count;
    SkillTable skills;

    uint needExpToUpgrade() const;

    uint calculateMaxHP() {
        return level*50 + 100;
    }
    uint calculateMaxMP() {
        return level*10 + 20;
    }
    uint calculateDamage() {
        return level*10 + 25;
    }
    uint calculateMaxUndeadCount() {
        return 1 + level/2;
    }
public:
    Player(Floor& f, std::pair<size_t,size_t> coord);
    uint damaged(IAttacker&, uint) override;

    void die() override;

    uint getCurrentControlledCount() const;
    uint getMaxUndeadCount() const;
    void addNewControlledUndead(Undead &undead);

    uint getDamage() const override;
    uint getMaxHp() const override;
    uint getCurrentHp() const override;

    void smartInteract(Field& f) override;

    void collectExperience(uint) override;
    void collectEssence(uint);
    void upgradeLevel();

    void useSkill(std::string, Object&);

    //! @todo нужны глобальные объекты для таблицы навыков
    void exploreNewUndeadType(std::string);
    void upgradeSkill(std::string);
};

#endif //LAB3_PLAYER_H
