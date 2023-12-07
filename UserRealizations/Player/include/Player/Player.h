#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H

#include <utility>
#include <vector>
#include <string>

#include <IExperienceCollector.h>
#include <IAttacker.h>

#include <Entity/Entity.h>
#include <Dungeon/Dungeon.h>
#include <SpecialElement/SpecialElement.h>
#include <SkillTable/SkillTable.h>

#include <Undead/Undead.h>
#include <Exceptions/PlayerExceptions.h>

class Player : public Entity, public IUpdatable, public ISmartInteractor, public IExperienceCollector {
private:
    uint level = 1;
    uint experience{};
    uint skill_points{};
    uint essence_count{};
    uint max_hp;
    uint current_hp;
    uint damage;
    uint max_mana_count;
    uint current_mana_count;

    std::unique_ptr<SkillTable> skills;

    uint max_undead_count;
    //! @todo Добавление указателей на контроллируемую нежить
//    std::vector<std::weak_ptr<UndeadType>> controlled_undead;
    uint current_undead_count = 0;

    uint needExpToUpgrade() const;

    uint calculateMaxHP() {
        return level*50 + 100;
    }
    uint calculateMaxMP() {
        return level*10 + 50;
    }
    uint calculateDamage() {
        return level*10 + 25;
    }
    uint calculateMaxUndeadCount() {
        return 1 + level/2;
    }
public:
    Player(Floor& f, std::pair<size_t,size_t> coord);
    Player(Floor& f, std::pair<size_t,size_t> coord, SkillTable *table);

    uint damaged(IAttacker&, uint) override;

    void die() override;

    uint getCurrentControlledCount() const;
    uint getMaxUndeadCount() const;
    void addNewControlledUndead(Undead &undead);

    uint getDamage() const override;
    uint getMaxHp() const override;
    uint getCurrentHp() const override;
    uint getMaxMP() const;
    uint getCurrentMP() const;

    void restoreHP(uint count);
    void restoreMP(uint count);

    void smartInteract(Field& f) override;

    void collectExperience(uint) override;
    void collectEssence(uint);
    void upgradeLevel();

    void useSkill(const std::string& name, const std::string& variation, Object& target);

    void exploreNewUndeadType(const std::string&);
    void upgradeSkill(const std::string&);

    const std::string getNaming() const override;
    const std::string getFullInfo() const override;
    const std::string getInfo() const override;
};

#endif //LAB3_PLAYER_H
