#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include <cstdlib>
#include <utility>
#include <string>
#include <mutex>

#include <IAttacker.h>

#include <Entity/Entity.h>

#include <SubSkill/SubSkill.h>
#include <EnemyType/EnemyType.h>

#include <Exceptions/EnemyExceptions.h>

class Enemy : public Entity {
private:
    std::weak_ptr<Entity> target_of_hunting;
    uint current_hp;
    std::unique_ptr<SubSkill> skill = nullptr;
    //!@brief мютекс на та, с этой сущностью уже кто-то что-то делает
    std::mutex m_is_target;
    std::mutex m_is_hunting;
protected:
    std::unique_ptr<EnemyType> type = nullptr;
public:
    Enemy(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<EnemyType>&& type, FRACTIONS fraction = FRACTIONS::ENEMY);
    Enemy(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<EnemyType>&& type, FRACTIONS fraction, std::unique_ptr<SubSkill>&& skill);

    virtual const std::string getTypeName() const = 0;
    const EnemyType& getBody() const {return *type;}
    const std::string getNaming() const override;
    const std::string getInfo() const override;
    uint getLevel() const;

    const Entity &getTarget() const;

    uint getMaxHp() const override;
    uint getCurrentHp() const override;
    uint getDamage() const override;
    uint getExperienceCount() const;

    /*!
     * @throws enemy_errors::invalid_skill_error if no skill to use;
     */
    void useSkill(Object& target);
    void damaged(IAttacker& attacker, uint damage) override;

    void scanTerritory();
    void hunt();
};

#endif //LAB3_ENEMY_H
