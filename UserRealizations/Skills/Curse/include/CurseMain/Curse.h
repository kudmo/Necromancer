#ifndef LAB3_CURSE_H
#define LAB3_CURSE_H

#include <string>
#include <MainSkill/MainSkill.h>

class Curse : public MainSkill {
private:
    uint price = 10;
public:
    Curse() = default;
    explicit Curse(uint level): MainSkill(level) {}
    explicit Curse(std::map<std::string, SubSkill*> skills): MainSkill(std::move(skills)) {}
    void checkUser(Entity *) override;
    void checkTarget(Object *) override;
    void checkVariation(SubSkill *) override;
    std::string getName() noexcept override;
};

#endif //LAB3_CURSE_H
