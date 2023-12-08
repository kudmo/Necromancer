#ifndef LAB3_MAINSKILLBUILDER_H
#define LAB3_MAINSKILLBUILDER_H

#include "MainSkill/MainSkill.h"
#include <memory>

class MainSkillBuilder {
public:
    virtual std::unique_ptr<MainSkill> build(uint level) const = 0;
    virtual ~MainSkillBuilder() = default;
};

#endif //LAB3_MAINSKILLBUILDER_H
