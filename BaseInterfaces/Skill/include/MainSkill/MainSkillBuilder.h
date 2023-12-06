#ifndef LAB3_MAINSKILLBUILDER_H
#define LAB3_MAINSKILLBUILDER_H

#include "MainSkill/MainSkill.h"

class MainSkillBuilder {
public:
    virtual MainSkill *build(uint level) const = 0;
    virtual ~MainSkillBuilder() = default;
};

#endif //LAB3_MAINSKILLBUILDER_H
