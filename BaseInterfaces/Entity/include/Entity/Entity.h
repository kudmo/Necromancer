#ifndef LAB3_ENTITY_H
#define LAB3_ENTITY_H

#include <cstdlib>
#include <utility>

#include <IAttacker.h>
#include <IAttackable.h>
#include <IMovable.h>

#include <Object/Object.h>
#include <Exceptions/DungeonExceptions.h>

class Floor;
enum class DIRECTIONS;
class SkillTable;
class MainSkill;

enum class FRACTIONS {
    //! @todo Фракции прописать
    ENEMY,
    PLAYER,
};

class Entity : public Object, public IAttackable, public IAttacker, public IMovable {
private:
    DIRECTIONS direction;
    FRACTIONS fraction;
public:
    Entity(Floor& f, std::pair<size_t,size_t> coord, FRACTIONS fraction);

    void move() override;
    void rotate(DIRECTIONS dir) override;
    void stay() override;

    DIRECTIONS getDirection() const;

    FRACTIONS getFraction() const;


    virtual uint getMaxHp() const = 0;
    virtual uint getCurrentHp() const = 0;
    virtual uint getDamage() const = 0;

    void attack(IAttackable& target) override;
    virtual void die();
};

#endif //LAB3_ENTITY_H
