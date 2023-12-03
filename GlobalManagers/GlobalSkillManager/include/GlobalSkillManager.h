#ifndef LAB3_GLOBALSKILLTABLE_H
#define LAB3_GLOBALSKILLTABLE_H

#include <vector>
#include <string>

#include "SkillTable/SkillTable.h"
#include "MainSkill/MainSkill.h"
#include "SubSkill/SubSkill.h"

class GlobalSkillManager {
public:
    static SkillTable* buildSkillTable(const std::map<std::string, std::vector<std::string>>&);
    static SkillTable* buildSkillTableDefault(const std::vector<std::string>&);

    static MainSkill *buildDefaultMainSkill(const std::string & naming, uint level = 1);
    static MainSkill *buildMainSkill(const std::string &naming, const std::vector<std::string>& variations, uint level = 1);

    static SubSkill *buildSubSkill(const std::string &);
};

#endif //LAB3_GLOBALSKILLTABLE_H
