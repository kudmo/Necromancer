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

enum class FRACTIONS {
    ENEMY,
    PLAYER,
};
#pragma GCC diagnostic ignored "-Wunused-function"
static  std::string convertFractionToStr(FRACTIONS fraction) {
    switch (fraction) {
        case FRACTIONS::PLAYER:
            return std::string("Player_fraction");
            break;
        case FRACTIONS::ENEMY:
            return std::string("Enemy_fraction");
            break;
    }
}
#pragma GCC diagnostic ignored "-Wunused-function"
static FRACTIONS convertStrToFraction(const std::string& fraction) {
    if (fraction == "Player_fraction")
        return FRACTIONS::PLAYER;
    else if (fraction == "Enemy_fraction")
        return FRACTIONS::ENEMY;
    else
        throw std::invalid_argument(std::string("Unknown fraction name: ") + fraction);
}

class Entity : public Object, public IAttackable, public IAttacker, public IMovable {
private:
    DIRECTIONS direction;
    FRACTIONS fraction;
    bool dead = false;
public:
    Entity(Floor& f, std::pair<size_t,size_t> coord, FRACTIONS fraction);
    bool isDead() const {return dead;}

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

    virtual const std::string getNaming() const = 0;
    virtual const std::string getFullInfo() const = 0;

};

class EntityService {

};
#endif //LAB3_ENTITY_H
