#include "GlobalCoverageManager.h"
#include "Dungeon/Dungeon.h"

#include "Coverage/CoverageBuilder.h"
#include "Magma/MagmaBuilder.h"

const Coverage &GlobalCoverageManager::build(const std::string &naming, Dungeon &dungeon, size_t level,
                                             std::pair<size_t, size_t> coordinates) {
    static std::map<std::string, std::shared_ptr<CoverageBuilder>> builder_map {
            {"magma", std::make_shared<MagmaBuilder>()}};

    try {
        auto &builder = builder_map.at(naming);
        return builder->build(dungeon, level, coordinates);
    } catch (std::out_of_range&) {
        throw std::out_of_range(std::string("No coverages to build with this name: ") + naming);
    }
}
