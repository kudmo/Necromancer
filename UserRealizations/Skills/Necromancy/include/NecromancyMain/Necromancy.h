#ifndef LAB3_NECROMANCY_H
#define LAB3_NECROMANCY_H

#include <string>
#include <MainSkill/MainSkill.h>
#include <MainSkill/MainSkillBuilder.h>

class Necromancy : public MainSkill{
private:
    uint price;
public:
    Necromancy() = default;
    Necromancy(uint level) : MainSkill(level) {}
    /*!
     * @throws skill_errors::invalid_skill_user if user isn't player
     */
    void checkUser(Entity *) override;
    /*!
     * @throws skill_errors::invalid_skill_target if target isn't entity
     */
    void checkTarget(Object *) override;
    /*!
     * @throws skill_errors::invalid_subskill_type_error if subskill isn't variation of necromancy
     */
    void checkVariation(SubSkill *) override;
    const std::string getName() const noexcept override;
};

class NecromancyBuilder : public MainSkillBuilder {
public:
    MainSkill *build(uint level) const override;
};
#endif //LAB3_NECROMANCY_H
