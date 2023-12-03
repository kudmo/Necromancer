#ifndef LAB3_CURSE_H
#define LAB3_CURSE_H

#include <string>
#include <MainSkill/MainSkill.h>
#include <MainSkill/MainSkillBuilder.h>

class Curse : public MainSkill {
private:
    uint price = 10;
public:
    Curse() = default;
    explicit Curse(uint level): MainSkill(level) {}
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;
    void checkVariation(SubSkill *) override;
    const std::string getName() const noexcept override;
};

class CurseBuilder : public MainSkillBuilder {
public:
    MainSkill *build(uint level) const override;
};
#endif //LAB3_CURSE_H
