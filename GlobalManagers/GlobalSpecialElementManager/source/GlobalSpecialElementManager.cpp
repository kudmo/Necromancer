#include <map>
#include "GlobalSpecialElementManager.h"
#include "Dungeon/Dungeon.h"

#include "Door/DoorBuilder.h"
#include "Wall/WallBuilder.h"
#include "Ladder/LadderBuilder.h"

#include <iostream>

const SpecialElement& GlobalSpecialElementManager::build(const std::string& naming, Dungeon& dungeon, size_t level, std::pair<size_t,size_t> coordinates) {
    static std::map<std::string, std::shared_ptr<SpecialElementBuilder>> builder_map {
        {"wall", std::make_shared<WallBuilder>()},
        {"door", std::make_shared<DoorBuilder>()},
        {"ladder", std::make_shared<LadderBuilder>()}};

    try {
        auto &builder = builder_map.at(naming);
        return builder->build(dungeon, level, coordinates);
    } catch (std::out_of_range&) {
        throw std::out_of_range(std::string("No element to build with this name: ") + naming);
    }
}
