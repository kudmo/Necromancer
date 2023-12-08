#ifndef LAB3_CURSEVARIATION_H
#define LAB3_CURSEVARIATION_H

#include <SubSkill/SubSkill.h>
#include <SubSkill/SubSkillBuilder.h>

#include <Exceptions/SkillExceptions.h>

class CurseVariation : public SubSkill {
private:
    uint calculateDamage(uint level) const {return 10 + (level-1)*1.2;}
public:
    CurseVariation() = default;
    /*!
     * @throws skill_errors::invalid_skill_target if Target isn't entity
     */
    void skill(uint level, Entity &user, Object &target) override;
    uint getCost(uint level, const Object&) override {return 10;}
    std::string getName() override {return std::string("curse");}
};

class CurseVariationBuilder : public SubSkillBuilder {
public:
    std::unique_ptr<SubSkill> build() const override;
};

#endif //LAB3_CURSEVARIATION_H
