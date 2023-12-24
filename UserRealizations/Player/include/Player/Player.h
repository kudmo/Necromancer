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
    //!@brief мютекс на та, с этой сущностью уже кто-то что-то делает
    std::mutex m_is_target;

    //!@brief мютекс на та, с эта сущность улучщается
    std::mutex m_is_upgrading;

    //!@brief мютекс на та, нужно получить характеристики
    std::mutex m_charact;

    uint level = 1;
    uint experience = 0;
    uint skill_points = 0;
    uint essence_count = 0;
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

/*!@brief
 * 0 - move
 * 1 - attack
 * 2 - interacting
 * 3 - using skill
 */
    std::bitset<4> active_states = 0x0000;
/*!@brief
 * 0 - damaged
 * 1 - dead
 */
    std::bitset<2> passive_states = 0x00;
    void setStateMoving() {active_states = 0x0001;}
    void setStateAttacking() { active_states = 0x0010;}
    void setStateInteracting() {active_states = 0x1000;}
    void setStateSkillUsing() { active_states = 0x0100;}
    void setStateDamaged() {passive_states[0] = true;}
    void setStateDead() {passive_states[1] = true;}

    std::vector<std::string> known_undead_types;
public:
    Player(Floor& f, std::pair<size_t,size_t> coord);
    Player(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<SkillTable>&& table);

    void move() override;

    void attack(IAttackable &target) override;
    void damaged(IAttacker&, uint) override;

    void die() override;

    uint getCurrentControlledCount() const;
    uint getMaxUndeadCount() const;
    void addNewControlledUndead(Undead &undead);

    uint getDamage() const override;
    uint getMaxHP() const override;
    uint getCurrentHP() const override;
    uint getMaxMP() const;
    uint getCurrentMP() const;
    uint getExperience() const;
    uint getSkillPoints() const;
    uint getEssenceCount() const;
    uint getLevel() const;

    void resetState() override {
        active_states = 0x0000;
        passive_states[0] = false;
    }
    bool isMoving() const final {return active_states[0];}
    bool isAttacking() const final {return active_states[1];}
    bool isSkillUsed() const {return active_states[2];}
    bool isInteracting() const {return active_states[3];}
    bool isDammaged() const final {return passive_states[0];}
    bool isDead() const final {return passive_states[1];}


    void restoreHP(uint count);
    void restoreMP(uint count);

    void smartInteract(Field& f) override;

    void collectExperience(uint) override;
    void collectEssence(uint);
    void upgradeLevel();

    void checkSkillTarget(const std::string& name, const std::string& variation, Object& target);
    void useSkill(const std::string& name, const std::string& variation, Object& target);
    std::vector<std::string> getAllSkills() const;
    std::vector<std::string> getAllSubSkills() const;
    void exploreNewUndeadType(const std::string&);
    void upgradeSkill(const std::string&);
    std::vector<std::string> getAllExploredUndeadTypes() const;

    const std::string getNaming() const override;
    const std::string getFullInfo() const override;
    const std::string getInfo() const override;
};

#endif //LAB3_PLAYER_H
