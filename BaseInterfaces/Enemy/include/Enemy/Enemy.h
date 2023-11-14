#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include <cstdlib>
#include <utility>
#include <string>

#include "../../../../BaseInterfaces/Interfaces/IExperienceCollector.h"

#include "../../../Entity/include/Entity/Entity.h"
#include "../../../EnemyType/include/EnemyType/EnemyType.h"
#include "../../../Interfaces/IAttacker.h"

class Enemy : public Entity {
private:
    Entity *target;
    uint current_hp;
protected:
    EnemyType *type;
public:
    Enemy(EnemyType& type, FRACTIONS fraction = FRACTIONS::ENEMY): Entity(fraction) {
        this->type = &type;
        this->current_hp = type.getMaxHp();
    }

    std::string getNaming() const {
        return type->getNaming();
    }
    const Entity &getTarget() const {
        return *target;
    }

    uint getMaxHp() const override {
        return type->getMaxHp();
    }
    uint getCurrentHp() const override {
        return current_hp;
    }
    uint getDamage() const override {
        return type->getDamage();
    }
    uint getExperienceCount() const {
        return type->getExperienceCount();
    }


    uint damaged(IAttacker& attacker, uint damage) override {
        auto r_damage = std::min(damage, current_hp);
        current_hp -= r_damage;
        if (current_hp == 0) {
            IExperienceCollector *temp = dynamic_cast<IExperienceCollector*>(&attacker);
            if (temp)
                temp->collectExperience(getExperienceCount());
            die();
        }
        return r_damage;
    }

    //! @todo Алгоритм поиска и приследования
    void scanTerritory();
    void hunt();

};

#endif //LAB3_ENEMY_H
