#include "UndeadManager.h"




UndeadManager::UndeadManager(std::string path) {
    fs::path dirPath(path);
    for(auto& dir : fs::directory_iterator(dirPath)) {
        if (dir.is_directory()) {
            for (auto &file : fs::directory_iterator(fs::path(dir))) {
                if((file.is_regular_file() || file.is_symlink()) && file.path().extension() == ".so") {
                    auto lib = open(file.path());
                    auto getName = reinterpret_cast<std::string(*)()>(dlsym(lib, "getName"));
                    libs.emplace(getName(), lib);
                    auto getBuilder = reinterpret_cast<UndeadBuilder&(*)()>(dlsym(lib, "getBuilder"));
                    UndeadBuilder& b = getBuilder();
                    enemy_builders.emplace(getName(), b);
                    auto getTypeBuilder = reinterpret_cast<UndeadTypeBuilder&(*)()>(dlsym(lib, "getTypeBuilder"));
                    type_builders.emplace(getName(), getTypeBuilder());
                }
            }
        }
    }
}

const std::vector<std::string> UndeadManager::getAllUndeadTypes() const {
    std::vector<std::string> res;
    res.reserve(libs.size());
    for (auto &i : libs) {
        res.push_back(i.first);
    }
    return res;
}
UndeadManager::~UndeadManager() {
    for (auto &lib : libs)
        close(lib.second);
}

Enemy &UndeadManager::build(const std::string &enemy_naming, Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coordinates, uint level,
                            std::unique_ptr<AliveType> &&dead, FRACTIONS fraction) const {
    try {
        auto &builder = enemy_builders.at(enemy_naming);
        return builder.get().build(dungeon, floor, coordinates, level, std::move(dead), fraction);
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No undead to build with this name: ") + enemy_naming);
    }
}

std::unique_ptr<EnemyType>
UndeadManager::build(const std::string &enemy_naming, uint level, std::unique_ptr<AliveType> &&who) const {
    try {
        auto &builder = type_builders.at(enemy_naming);
        return builder.get().build(level, std::move(who));
    } catch (std::out_of_range&) {
        throw std::invalid_argument(std::string("No undead to build with this name: ") + enemy_naming);
    }
}
