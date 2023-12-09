#ifndef LAB3_UNDEADTYPE_H
#define LAB3_UNDEADTYPE_H

#include <cstdlib>
#include <memory>

#include <EnemyType/EnemyType.h>
#include <AliveType/AliveType.h>

class UndeadType : public EnemyType {
private:
    std::unique_ptr<AliveType> who_it_was;
public:
    UndeadType(uint level, std::unique_ptr<AliveType>&& who);

    const AliveType &getWhoItWas() const;
    uint calculateMaxHp(uint level) const override;
    uint calculateDamage(uint level) const override;
    uint calculateExperienceCount(uint level) const override;
    virtual double calculateCoefficient(uint level) const = 0;

    double getCoefficient() const;

    std::unique_ptr<AliveType> takeInnerBody();
};
#endif //LAB3_UNDEADTYPE_H
