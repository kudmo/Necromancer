#ifndef LAB3_MORPHISM_H
#define LAB3_MORPHISM_H

#include <string>
#include "MainSkill/MainSkill.h"
#include "MainSkill/MainSkillBuilder.h"

class Morphism : public MainSkill {
public:
    Morphism(uint level) : MainSkill(level) {}
    void checkVariation(SubSkill *) override;
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;

    const std::string getName() const noexcept override;
};

class MorphismBuilder : public MainSkillBuilder {
public:
    MainSkill *build(uint level) const override;
};
#endif //LAB3_MORPHISM_H
