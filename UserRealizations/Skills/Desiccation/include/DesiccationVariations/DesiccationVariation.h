#ifndef LAB3_DESICCATIONVARIATION_H
#define LAB3_DESICCATIONVARIATION_H

#include <SubSkill/SubSkill.h>
#include <SubSkill/SubSkillBuilder.h>

#include "EnemyType/EnemyType.h"

class DesiccationVariation : public SubSkill {
public:
    void checkUser(Entity *entity) override;

    void checkTarget(Object *object) override;

    uint getCost(uint level, const Object&) override {return 20;}
};

class DesiccationVariationMana : public DesiccationVariation {
private:
    uint calculateProfit(uint level, const EnemyType& ) const;
public:
    void skill(uint level, Entity &, Object &) override;
    std::string getName() override;
};
class DesiccationVariationHealth : public DesiccationVariation {
private:
    uint calculateProfit(uint level, const EnemyType& ) const;
public:
    void skill(uint level, Entity &, Object &) override;
    std::string getName() override;
};

class DesiccationVariationManaBuilder : public SubSkillBuilder {
public:
    std::unique_ptr<SubSkill> build() const override;
};

class DesiccationVariationHealthBuilder : public SubSkillBuilder {
public:
    std::unique_ptr<SubSkill> build() const override;
};

#endif //LAB3_DESICCATIONVARIATION_H
