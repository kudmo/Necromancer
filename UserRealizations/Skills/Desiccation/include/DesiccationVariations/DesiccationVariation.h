#ifndef LAB3_DESICCATIONVARIATION_H
#define LAB3_DESICCATIONVARIATION_H

#include <SubSkill/SubSkill.h>
#include <SubSkill/SubSkillBuilder.h>

#include "EnemyType/EnemyType.h"

class DesiccationVariation : public SubSkill {
public:
    uint getCost(uint level, const Object&) override {return 50;}
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
    SubSkill *build() const override;
};

class DesiccationVariationHealthBuilder : public SubSkillBuilder {
public:
    SubSkill *build() const override;
};

#endif //LAB3_DESICCATIONVARIATION_H