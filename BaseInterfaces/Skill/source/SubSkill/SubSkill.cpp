#include <SubSkill/SubSkill.h>

SubSkill::SubSkill(uint level) : level(level) {}

void SubSkill::setLevel(uint level) {
    this->level = level;
}

uint SubSkill::getLevel() const {
    return level;
}

