#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <mutex>

#include <MainSkill/MainSkill.h>
#include <SubSkill/SubSkill.h>

#include <Exceptions/SkillExceptions.h>

class Object;
class Entity;

class SkillTable {
private:
    std::mutex m_is_upgrading;
    std::map<std::string, std::unique_ptr<MainSkill>> skills;
public:
    SkillTable() = default;
    //! @todo подумать над копированием, уникальностью и тп
    SkillTable(SkillTable&& moved) noexcept;
    SkillTable& operator=(SkillTable&& moved) noexcept;

    const std::string getInfo() const noexcept;
/*!
 * @throws skill_errors::invalid_subskill_error if Skill with this name already was added
 */
    void addSkill(std::unique_ptr<MainSkill>&&);
/*!
 * @throws skill_errors::invalid_subskill_error if Subskill with this name already was added
 */
    void addSkillVariation(std::string,  std::unique_ptr<SubSkill>&& SubSkill);

    const std::vector<std::string> getAllSkills() const;

    const std::map<std::string, std::vector<std::string>> getAllVariations() const;

/*!
 * @throws skill_errors::invalid_skill_level if current level is max
 */
    void upgradeSkill(std::string name);

    uint getCost(std::string name, std::string subname, const Object&) const;
/*!
 * @throws skill_errors::skill_table_no_skill_error if No skill with this name
 * @throws skill_errors::invalid_subskill_error if no subskill with this name
 */
    void useSkill(std::string name, std::string subname, Entity& user, Object& target);
    ~SkillTable() = default;
};