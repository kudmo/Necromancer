#ifndef LAB3_ENEMYTYPE_H
#define LAB3_ENEMYTYPE_H

#include <utility>
#include <string>

class EnemyType {
private:
    uint level;
public:
    explicit EnemyType(uint level);

    virtual const std::string getNaming() const = 0;

    uint getLevel() const;

    virtual uint calculateMaxHp(uint level) const = 0;
    virtual uint calculateDamage(uint level) const = 0;
    virtual uint calculateExperienceCount(uint level) const = 0;

    uint getMaxHp() const ;
    uint getDamage() const;
    uint getExperienceCount() const;

    virtual ~EnemyType() = default;
};
#endif //LAB3_ENEMYTYPE_H
