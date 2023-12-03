#include "GlobalSkillManager.h"
#include <memory>

#include "SubSkill/SubSkillBuilder.h"
#include "NecromancyVariations/NecromancyVariation.h"
#include "CurseVariations/CurseVariation.h"

#include "Skeleton/Skeleton.h"
#include "Skeleton/NecromancyAsSkeleton.tcc"
#include "Ghoul/Ghoul.h"
#include "Ghoul/NecromancyAsGhoul.tcc"

#include "MainSkill/MainSkillBuilder.h"
#include "NecromancyMain/Necromancy.h"
#include "CurseMain/Curse.h"


SubSkill *GlobalSkillManager::buildSubSkill(const std::string & naming) {
    static std::map<std::string, std::shared_ptr<SubSkillBuilder>> builder_map {
        // Necromancy
            {"necromancy_skeleton", std::make_shared<NecromancyAsBuilder<Skeleton>>()},
            {"necromancy_ghoul", std::make_shared<NecromancyAsBuilder<Ghoul>>()},
        // Curse
            {"curse", std::make_shared<CurseVariationBuilder>()}
    };
    try {
        auto &builder = builder_map.at(naming);
        return builder->build();
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No subskill to build with this name: ") + naming);
    }
}

MainSkill *GlobalSkillManager::buildDefaultMainSkill(const std::string &naming, uint level) {
    static std::map<std::string, std::shared_ptr<MainSkillBuilder>> builder_map {
        // Necromancy
            {"necromancy", std::make_shared<NecromancyBuilder>()},
        // Curse
            {"curse", std::make_shared<CurseBuilder>()}
    };
    static std::map<std::string, std::string> default_skills {
            // Necromancy
            {"necromancy", "necromancy_skeleton"},
            // Curse
            {"curse", "curse"}
    };

    try {
        auto &builder = builder_map.at(naming);
        auto main = builder->build(level);
        auto default_sub = buildSubSkill(default_skills[naming]);
        main->addVariation(default_sub);
        return main;
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No subskill to build with this name: ") + naming);
    }
}

MainSkill *GlobalSkillManager::buildMainSkill(const std::string &naming, const std::vector<std::string> &variations, uint level) {
    MainSkill *skill = buildDefaultMainSkill(naming, level);
    try {
        for (auto &i : variations) {
            SubSkill *subskill = buildSubSkill(i);
            skill->addVariation(subskill);
        }
    } catch (...) {
        delete skill;
        throw ;
    }

    return skill;
}

SkillTable *GlobalSkillManager::buildSkillTable(const std::map<std::string, std::vector<std::string>> &mainskill_map) {
    auto *table = new SkillTable();
    try {
        for (auto &i: mainskill_map) {
            MainSkill *skill = buildMainSkill(i.first, i.second);
            table->addSkill(skill);
        }
    } catch (...) {
        delete table;
        throw ;
    }
    return table;
}

SkillTable *GlobalSkillManager::buildSkillTableDefault(const std::vector<std::string> & mainskill_map) {
    auto *table = new SkillTable();
    try {
        for (auto &i: mainskill_map) {
            MainSkill *skill = buildDefaultMainSkill(i);
            table->addSkill(skill);
        }
    }catch (...) {
        delete table;
        throw ;
    }
    return table;
}
