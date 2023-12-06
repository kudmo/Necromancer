#include "GlobalSkillManager.h"
#include <memory>

#include "SubSkill/SubSkillBuilder.h"
#include "NecromancyVariations/NecromancyVariation.h"
#include "CurseVariations/CurseVariation.h"
#include "DesiccationVariations/DesiccationVariation.h"
#include "MorphismVariations/MorphismVariation.h"

#include "Skeleton/Skeleton.h"
#include "Skeleton/NecromancyAsSkeleton.tcc"
#include "Skeleton/MorphismAsSkeleton.tcc"

#include "Ghoul/Ghoul.h"
#include "Ghoul/NecromancyAsGhoul.tcc"
#include "Ghoul/MorphismAsGhoul.tcc"

#include "MainSkill/MainSkillBuilder.h"
#include "NecromancyMain/Necromancy.h"
#include "CurseMain/Curse.h"
#include "DesiccationMain/Desiccation.h"
#include "MorphismMain/Morphism.h"

SubSkill *GlobalSkillManager::buildSubSkill(const std::string & naming) {
    static std::map<std::string, std::shared_ptr<SubSkillBuilder>> builder_map {
        // Curse
            {"curse", std::make_shared<CurseVariationBuilder>()},
        // Desiccation
            {"desiccation_mana", std::make_shared<DesiccationVariationManaBuilder>()},
            {"desiccation_health", std::make_shared<DesiccationVariationHealthBuilder>()},
        // Necromancy
            {"necromancy_skeleton", std::make_shared<NecromancyAsBuilder<Skeleton>>()},
            {"necromancy_ghoul", std::make_shared<NecromancyAsBuilder<Ghoul>>()},
        // Morphism
            {"morphism_skeleton", std::make_shared<MorphismAsBuilder<Skeleton>>()},
            {"morphism_ghoul", std::make_shared<MorphismAsBuilder<Ghoul>>()},

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
            {"curse", {"curse"}},
        // Desiccation
            {"desiccation", {"desiccation_mana", "desiccation_health"}},
        // Necromancy
            {"necromancy", {"necromancy_skeleton"}},
        // Morphism
            {"morphism", {"morphism_skeleton"}},
    };

    MainSkill *main = nullptr;
    try {
        auto &builder = builder_map.at(naming);
        main = builder->build(level);

        for (auto &i : default_skills[naming]) {
            auto default_sub = buildSubSkill(i);
            main->addVariation(default_sub);
        }
        return main;
    } catch (...) {
        delete main;
        throw ;
    }
}

MainSkill *GlobalSkillManager::buildMainSkill(const std::string &naming, const std::vector<std::string> &variations, uint level) {
    MainSkill *skill = buildDefaultMainSkill(naming, level);
    try {
        for (auto &i : variations) {
            SubSkill *subskill = buildSubSkill(i);
            skill->addVariation(subskill);
        }
    } catch (std::out_of_range&) {
        delete skill;
        throw std::invalid_argument(std::string("No subskill to build with this name: ") + naming);
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
