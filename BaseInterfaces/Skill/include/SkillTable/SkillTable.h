#pragma once

#include <map>
#include <string>
#include <stdexcept>

#include "../../../Entity/include/Entity/Entity.h"
#include "../../../Object/include/Object/Object.h"

#include "../MainSkill/MainSkill.h"
#include "../SubSkill/SubSkill.h"

#include "../Exeptions/SkillException.h"

class SkillTable {
private:
    //!@todo поменять на wrapper std::reference_wrapper (<functional>)
    std::map<std::string, MainSkill&> skills;
public:
    SkillTable() = default;
    SkillTable(std::map<std::string, MainSkill&> skills);

    /*!
     * @throws skill_errors::invalid_subskill_error if Skill with this name already was added
     */
    void addSkill(MainSkill&);
    /*!
     * @throws skill_errors::invalid_subskill_error if Subskill with this name already was added
     */
    void addSkillVariation(std::string, SubSkill*);

    const std::vector<std::string> getAllSkills() const;

    const std::map<std::string, std::vector<std::string>> getAllVariations() const;

/*!
 * @throws skill_errors::invalid_skill_level if current level is max
 */
    void upgradeSkill(std::string name);

/*!
 * @throws skill_errors::skill_table_no_skill_error if No skill with this name
 */
    void useSkill(std::string name, Entity& user, Object& target);

/*!
 * @throws skill_errors::skill_table_no_skill_error if No skill with this name
 * @throws skill_errors::invalid_subskill_error if no subskill with this name
 */
    void useSkillVariation(std::string name, std::string subname, Entity& user, Object& target);
};