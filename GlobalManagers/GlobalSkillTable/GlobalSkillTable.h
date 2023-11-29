#ifndef LAB3_GLOBALSKILLTABLE_H
#define LAB3_GLOBALSKILLTABLE_H

#include "../../BaseInterfaces/Skill/include/SkillTable/SkillTable.h"
#include "../../BaseInterfaces/Skill/include/MainSkill/MainSkill.h"

inline static SkillTable& getGlobalTable() {
    std::map<std::string, MainSkill&> skills;
    static SkillTable table = SkillTable(skills);
    return table;
}
#endif //LAB3_GLOBALSKILLTABLE_H
