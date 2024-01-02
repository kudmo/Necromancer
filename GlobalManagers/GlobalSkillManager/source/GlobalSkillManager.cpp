#include "GlobalSkillManager.h"
#include "GlobalEnemyManager.h"
#include <memory>

#include "SubSkill/SubSkillBuilder.h"
#include "NecromancyVariations/NecromancyVariation.h"
#include "CurseVariations/CurseVariation.h"
#include "DesiccationVariations/DesiccationVariation.h"
#include "MorphismVariations/MorphismVariation.h"

#include "MainSkill/MainSkillBuilder.h"
#include "NecromancyMain/Necromancy.h"
#include "CurseMain/Curse.h"
#include "DesiccationMain/Desiccation.h"
#include "MorphismMain/Morphism.h"

std::unique_ptr<SubSkill> GlobalSkillManager::buildSubSkill(const std::string & naming) {
    static std::map<std::string, std::shared_ptr<SubSkillBuilder>> builder_map {
        // Curse
            {"curse_curse", std::make_shared<CurseVariationBuilder>()},
        // Desiccation
            {"desiccation_mana", std::make_shared<DesiccationVariationManaBuilder>()},
            {"desiccation_health", std::make_shared<DesiccationVariationHealthBuilder>()},
    };
    auto main_name = naming.substr(0, naming.find("_"));
    auto sub_name = naming.substr(naming.find("_") + 1);

    if (main_name == "necromancy") {
        return GlobalEnemyManager::getInstance().buildNecromancy(sub_name);
    } else if (main_name == "morphism") {
        return GlobalEnemyManager::getInstance().buildMorphism(sub_name);
    }

    try {
        auto &builder = builder_map.at(naming);
        return builder->build();
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No subskill to build with this name: ") + naming);
    }
}

std::unique_ptr<MainSkill> GlobalSkillManager::buildDefaultMainSkill(const std::string &naming, uint level) {
    static std::map<std::string, std::shared_ptr<MainSkillBuilder>> builder_map {
        // Curse
            {"curse", std::make_shared<CurseBuilder>()},
        // Desiccation
            {"desiccation", std::make_shared<DesiccationBuilder>()},
        // Necromancy
            {"necromancy", std::make_shared<NecromancyBuilder>()},
        // Morphism
            {"morphism", std::make_shared<MorphismBuilder>()},
    };
    static std::map<std::string, std::vector<std::string>> default_skills {
        // Curse
            {"curse", {"curse_curse"}},
        // Desiccation
            {"desiccation", {"desiccation_mana", "desiccation_health"}},
        // Necromancy
            {"necromancy", {"necromancy_skeleton"}},
        // Morphism
            {"morphism", {"morphism_skeleton"}},
    };

    try {
        auto &builder = builder_map.at(naming);
        auto main = builder->build(level);

        for (auto &i : default_skills[naming]) {
            auto default_sub = buildSubSkill(i);
            main->addVariation(std::move(default_sub));
        }
        return main;
    } catch (...) {
        throw ;
    }
}

std::unique_ptr<MainSkill> GlobalSkillManager::buildMainSkill(const std::string &naming, const std::vector<std::string> &variations, uint level) {
    auto skill = buildDefaultMainSkill(naming, level);
    try {
        for (auto &i : variations) {
            auto subskill = buildSubSkill(i);
            skill->addVariation(std::move(subskill));
        }
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No subskill to build with this name: ") + naming);
    }

    return skill;
}

std::unique_ptr<SkillTable> GlobalSkillManager::buildSkillTable(const std::map<std::string, std::vector<std::string>> &mainskill_map) {
    auto table = std::make_unique<SkillTable>();
    for (auto &i: mainskill_map) {
        auto skill = buildMainSkill(i.first, i.second);
        table->addSkill(std::move(skill));
    }
    return table;
}

std::unique_ptr<SkillTable> GlobalSkillManager::buildSkillTableDefault(const std::vector<std::string> & mainskill_map) {
    auto table = std::make_unique<SkillTable>();
    for (auto &i: mainskill_map) {
        auto skill = buildDefaultMainSkill(i);
        table->addSkill(std::move(skill));
    }
    return table;
}
