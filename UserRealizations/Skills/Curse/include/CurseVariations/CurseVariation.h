#ifndef LAB3_CURSEVARIATION_H
#define LAB3_CURSEVARIATION_H

#include <SubSkill/SubSkill.h>

#include <Exceptions/SkillExceptions.h>

class CurseVariation : public SubSkill {
private:
    uint damage = 10;
public:
    CurseVariation() = default;
    explicit CurseVariation(uint level) : SubSkill(level) {}
    /*!
     * @throws skill_errors::invalid_skill_target if Target isn't entity
     */
    void skill(Entity &user, Object &target) override;
    uint getCost() override {return 1;}
    void Upgrade() override {damage += 1;setLevel(getLevel()+1);}
    std::string getName() override {return std::string("Curse");}
};
#endif //LAB3_CURSEVARIATION_H
