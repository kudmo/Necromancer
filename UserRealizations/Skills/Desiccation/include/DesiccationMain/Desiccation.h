#ifndef LAB3_DESICCATION_H
#define LAB3_DESICCATION_H


#include <string>
#include "MainSkill/MainSkill.h"
#include "MainSkill/MainSkillBuilder.h"

class Desiccation : public MainSkill {
public:
    explicit Desiccation(uint level) : MainSkill(level) {}
    void checkTarget(Object *) override;
    void checkUser(Entity *) override;
    void checkVariation(SubSkill *) override;

    const std::string getName() const noexcept override;
};

class DesiccationBuilder : public MainSkillBuilder {
public:
    MainSkill *build(uint level) const override;
};
#endif //LAB3_DESICCATION_H
