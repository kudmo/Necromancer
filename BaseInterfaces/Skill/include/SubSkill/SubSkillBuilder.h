#ifndef LAB3_SUBSKILLBUILDER_H
#define LAB3_SUBSKILLBUILDER_H

#include <memory>

#include "SubSkill/SubSkill.h"

class SubSkillBuilder {
public:
    virtual SubSkill* build() const = 0;
};

#endif //LAB3_SUBSKILLBUILDER_H
