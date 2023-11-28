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
    Entity *target;
    uint current_hp;
    // !@todo разобраться с типом указателя
    SubSkill* skill = nullptr;
protected:
    // !@todo разобраться с типом указателя
    EnemyType* type = nullptr;
public:
    Enemy(Floor& f, std::pair<size_t,size_t> coord, EnemyType* type, FRACTIONS fraction = FRACTIONS::ENEMY);
    Enemy(Floor& f, std::pair<size_t,size_t> coord, EnemyType *type,FRACTIONS fraction, SubSkill& skill);

    std::string getNaming() const ;
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

    //! @todo Алгоритм поиска и приследования
    void scanTerritory();
    void hunt();

    virtual ~Enemy() override;
};

#endif //LAB3_ENEMY_H
