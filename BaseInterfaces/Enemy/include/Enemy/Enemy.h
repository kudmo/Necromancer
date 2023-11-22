#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include <cstdlib>
#include <utility>
#include <string>

#include "../../../../BaseInterfaces/Interfaces/IExperienceCollector.h"
#include "../../../Interfaces/IAttacker.h"

#include "../../../Entity/include/Entity/Entity.h"
#include "../../../EnemyType/include/EnemyType/EnemyType.h"

#include "../Exceptions/EnemyExceptions.h"

class Enemy : public Entity {
private:
    Entity *target;
    uint current_hp;
protected:
    // !@todo разобраться с типом указателя
    EnemyType* type;
public:
    Enemy(Floor& f, std::pair<size_t,size_t> coord, EnemyType* type, FRACTIONS fraction = FRACTIONS::ENEMY);

    std::string getNaming() const ;
    const Entity &getTarget() const;

    uint getMaxHp() const override;
    uint getCurrentHp() const override;
    uint getDamage() const override;
    uint getExperienceCount() const;


    uint damaged(IAttacker& attacker, uint damage) override;

    //! @todo Алгоритм поиска и приследования
    void scanTerritory();
    void hunt();

    ~Enemy() {
        delete type;
    }
};

#endif //LAB3_ENEMY_H
