#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include <cstdlib>
#include <utility>
#include <string>
#include <mutex>
#include <memory>

#include <IAttacker.h>
#include <IPosisionable.h>

#include <Entity/Entity.h>

#include <SubSkill/SubSkill.h>
#include <EnemyType/EnemyType.h>

#include <Exceptions/EnemyExceptions.h>

/*!
 * @brief Base class for all enemy-classes
 */
class Enemy : public Entity {
private:
    std::weak_ptr<Entity> target_of_hunting;
    uint current_hp;
    std::unique_ptr<SubSkill> skill = nullptr;
    //!@brief мютекс на та, с этой сущностью уже кто-то что-то делает
    std::mutex m_is_target;

/*!@brief
 * 0 - move
 * 1 - attack
 */
    std::bitset<2> active_states = 0x00;
/*!@brief
 * 0 - damaged
 * 1 -dead
 */
    std::bitset<2> passive_states = 0x00;
    void setStateMoving() {
        active_states[0] = true;
        active_states[1] = false;
    }
    void setStateAttacking() {
        active_states[0] = false;
        active_states[1] = true;
    }
    void setStateDamaged() {passive_states[0] = true;}
    void setStateDead() {passive_states[1] = true;}
protected:
    std::unique_ptr<EnemyType> type = nullptr;
public:
    Enemy(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<EnemyType>&& type, FRACTIONS fraction = FRACTIONS::ENEMY);
    Enemy(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<EnemyType>&& type,  std::unique_ptr<SubSkill>&& skill, FRACTIONS fraction = FRACTIONS::ENEMY);

    void move() override;

    void resetState() override {
        active_states = 0x00;
        passive_states[0] = false;
    }
    bool isMoving() const final {return active_states[0];}
    bool isAttacking() const final {return active_states[1];}
    bool isDammaged() const final {return passive_states[0];}
    bool isDead() const final {return passive_states[1];}

    /*!
     * @return The name of the class to which this enemy belongs
     */
    virtual const std::string getTypeName() const = 0;
    /*!
     * @return The name of the type of this enemy
     */
    const std::string getNaming() const override;
    const std::string getInfo() const override;
    /*!
     * @return Level of enemy
     */
    uint getLevel() const;

    uint getMaxHP() const override;
    uint getCurrentHP() const override;
    uint getDamage() const override;
    /*!
     * @return The amount of experience that can be gained from the enemy
     */
    uint getExperienceCount() const;

    /*!
     * @throws enemy_errors::invalid_skill_error if no skill to use;
     */
    void useSkill(Object& target);
    void attack(IAttackable &target) override;
    void damaged(IAttacker& attacker, uint damage) override;

    /*!
     * @brief Looking for a target to hunt
     */
    void scanTerritory();
    /*!
     * @brief To pursue the target of the hunt
     */
    void hunt();
    void die() override;
};

#endif //LAB3_ENEMY_H
