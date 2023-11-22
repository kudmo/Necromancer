#ifndef LAB3_ENEMYTYPE_H
#define LAB3_ENEMYTYPE_H

#include <utility>
#include <string>

class EnemyType {
private:
    uint level;
public:
    EnemyType(uint level);

    virtual const std::string getNaming() const = 0;
    uint getLevel() const {return level;}
    virtual uint calculateMaxHp(uint level) const = 0;
    virtual uint calculateDamage(uint level) const = 0;
    virtual uint calculateExperienceCount(uint level) const = 0;

    uint getMaxHp() const {return calculateMaxHp(level);}
    uint getDamage() const {return calculateDamage(level);}
    uint getExperienceCount() const {return calculateExperienceCount(level);}

    virtual ~EnemyType() = default;
};
#endif //LAB3_ENEMYTYPE_H
