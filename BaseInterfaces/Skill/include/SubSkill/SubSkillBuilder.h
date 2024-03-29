#ifndef LAB3_SUBSKILLBUILDER_H
#define LAB3_SUBSKILLBUILDER_H

#include <memory>

#include "SubSkill/SubSkill.h"

class SubSkillBuilder {
public:
    virtual std::unique_ptr<SubSkill> build() const = 0;
    virtual ~SubSkillBuilder() = default;
};

#endif //LAB3_SUBSKILLBUILDER_H
