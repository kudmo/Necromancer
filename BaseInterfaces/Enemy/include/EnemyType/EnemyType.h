#ifndef LAB3_ENEMYTYPE_H
#define LAB3_ENEMYTYPE_H

#include <utility>
#include <string>

/*!
 * @brief Base class for all enemy-types
 */
class EnemyType {
private:
    uint level;
public:
    explicit EnemyType(uint level);

    /*!
     * @return The name of this type
     */
    virtual const std::string getNaming() const = 0;
    /*!
     * @return Level of enemy
     */
    uint getLevel() const;

    /*!
     * @param level Level of enemy
     * @return The max HP for a enemy of this type at a given level
     */
    virtual uint calculateMaxHp(uint level) const = 0;
    /*!
    * @param level Level of enemy
    * @return The damage for a enemy of this type at a given level
    */
    virtual uint calculateDamage(uint level) const = 0;
    /*!
    * @param level Level of enemy
    * @return The amount of experience for a enemy of this type at a given level
    */
    virtual uint calculateExperienceCount(uint level) const = 0;
    /*!
     * @return the maximum possible HP of the entity
     */
    uint getMaxHp() const ;
    /*!
     * @return the current HP value of the entity
     */
    uint getDamage() const;
    /*!
     * @return The amount of experience that can be gained from the enemy
     */
    uint getExperienceCount() const;

    virtual ~EnemyType() = default;
};
#endif //LAB3_ENEMYTYPE_H
