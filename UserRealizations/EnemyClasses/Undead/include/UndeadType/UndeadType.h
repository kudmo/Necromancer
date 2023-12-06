#ifndef LAB3_UNDEADTYPE_H
#define LAB3_UNDEADTYPE_H

#include <cstdlib>

#include <EnemyType/EnemyType.h>
#include <AliveType/AliveType.h>

class UndeadType : public EnemyType {
private:
    AliveType *who_it_was;
public:
    UndeadType(uint level, AliveType& who);

    const AliveType &getWhoItWas() const;
    uint calculateMaxHp(uint level) const override;
    uint calculateDamage(uint level) const override;
    uint calculateExperienceCount(uint level) const override;
    virtual double calculateCoefficient(uint level) const = 0;

    double getCoefficient() const;

    AliveType *takeInnerBody();

    ~UndeadType();
};
#endif //LAB3_UNDEADTYPE_H
