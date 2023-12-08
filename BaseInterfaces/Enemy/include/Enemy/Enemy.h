#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include <cstdlib>
#include <utility>
#include <string>

#include <IAttacker.h>

#include <Entity/Entity.h>
#include <Exceptions/EnemyExceptions.h>

class SubSkill;
class EnemyType;

class Enemy : public Entity {
private:
    Entity *target = nullptr;
    uint current_hp;
    // !@todo разобраться с типом указателя
    std::unique_ptr<SubSkill> skill = nullptr;
protected:
    // !@todo разобраться с типом указателя
    EnemyType* type = nullptr;
public:
    Enemy(Floor& f, std::pair<size_t,size_t> coord, EnemyType* type, FRACTIONS fraction = FRACTIONS::ENEMY);
    Enemy(Floor& f, std::pair<size_t,size_t> coord, EnemyType *type,FRACTIONS fraction, std::unique_ptr<SubSkill>&& skill);

    virtual const std::string getType() const = 0;
    const EnemyType& getBody() const {return *type;}
    const std::string getNaming() const override;
    const std::string getInfo() const override;
    uint getLevel() const;

    const Entity &getTarget() const;
    void setTarget(Entity&);

    uint getMaxHp() const override;
    uint getCurrentHp() const override;
    uint getDamage() const override;
    uint getExperienceCount() const;

    /*!
     * @throws enemy_errors::invalid_skill_error if no skill to use;
     */
    void useSkill(Object& target);
    uint damaged(IAttacker& attacker, uint damage) override;

    void scanTerritory();
    void hunt();

    virtual ~Enemy() override;
};

#endif //LAB3_ENEMY_H
