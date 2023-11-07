#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include <cstdlib>
#include <utility>
#include <string>

#include "../../../Entity/include/Entity/Entity.h"

#include "../../../EnemyType/include/EnemyType/EnemyType.h"

class Enemy : public Entity {
private:
    Entity *target;
    uint current_hp;
protected:
    EnemyType *type;
public:
    Enemy(EnemyType*);
    std::string getNaming() const;
    const Entity *getTarget() const {return target;}

    uint getMaxHp() const override;
    uint getCurrentHp() const override {return current_hp;}
    uint getDamage() const override;
    uint getExperienceCount() const;


    void attack(IAttackable &) override;
    uint damaged(uint) override;

    void interactWithCurrentField() override;
    void interactWithNextField() override;

    void scanTerritory();
    void hunt();
};
#endif //LAB3_ENEMY_H
