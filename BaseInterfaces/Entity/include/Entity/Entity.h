#ifndef LAB3_ENTITY_H
#define LAB3_ENTITY_H

#include <cstdlib>
#include <utility>
#include <stdexcept>

#include <IAttacker.h>
#include <IAttackable.h>
#include <IMovable.h>

#include <Object/Object.h>
#include <Exceptions/DungeonExceptions.h>
#include <bitset>

class Floor;
enum class DIRECTIONS;

enum class FRACTIONS {
    ENEMY,
    PLAYER,
};
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wreturn-type"
/*!
 * @param fraction enum member to convert
 * @return the string corresponding to the fraction enum member
 */
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
#pragma GCC diagnostic ignored "-Wreturn-type"
/*!
 * @param fraction string to convert
 * @return the enum member corresponding to the fraction string
 */
static FRACTIONS convertStrToFraction(const std::string& fraction) {
    if (fraction == "Player_fraction")
        return FRACTIONS::PLAYER;
    else if (fraction == "Enemy_fraction")
        return FRACTIONS::ENEMY;
    else
        throw std::invalid_argument(std::string("Unknown fraction name: ") + fraction);
}
/*!
 * @brief The base class for all creatures
 */
class Entity : public Object, public IAttackable, public IAttacker, public IMovable {
private:
    DIRECTIONS direction;
    FRACTIONS fraction;
public:
    Entity(Floor& f, std::pair<size_t,size_t> coord, FRACTIONS fraction);
    /*!
     * @brief Reset all states (except death) to the basic states
     */
    virtual void resetState() = 0;
    /*!
     * @return True if entity is already dead
     */
    virtual bool isDead() const = 0;
    /*!
     * @return True if entity is moving
     */
    virtual bool isMoving() const = 0;
    /*!
     * @return True if entity is attacking
     */
    virtual bool isAttacking() const = 0;
    /*!
     * @return True if entity is dammaged
     */
    virtual bool isDammaged() const = 0;

    /*!
     * @brief The entity is moving in his direction
     */
    void move() override;
    /*!
     * @brief The entity turns in the specified direction
     * @param dir specified direction
     */
    void rotate(DIRECTIONS dir) override;
    /*!
     * @brief The entity is standing still (standing methods are called, etc.)
     */
    void stay() override;
    /*!
     *
     * @return Current direction
     */
    DIRECTIONS getDirection() const;
    /*!
     *
     * @return A fraction of the entity
     */
    FRACTIONS getFraction() const;

    /*!
     * @return the maximum possible HP of the entity
     */
    virtual uint getMaxHP() const = 0;
    /*!
     * @return the current HP value of the entity
     */
    virtual uint getCurrentHP() const = 0;
    /*!
     * @returns the damage inflicted by the entity
     */
    virtual uint getDamage() const = 0;

    void attack(IAttackable& target) override;
    /*!
     * @brief Actions taking place at the moment of the entity's death
     */
    virtual void die();

};

#endif //LAB3_ENTITY_H
