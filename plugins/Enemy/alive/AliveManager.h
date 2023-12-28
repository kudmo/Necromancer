#ifndef LAB3_ALIVEMANAGER_H
#define LAB3_ALIVEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <dlfcn.h>
#include <filesystem>

#include "Enemy/Enemy.h"
#include "Dungeon/Dungeon.h"
#include "Alive/Alive.h"
#include "AliveType/AliveType.h"


namespace fs = std::filesystem;

class AliveManager {
private:
    void* open(const std::string& path) {
        void* lib = dlopen(path.c_str(), RTLD_NOW);
        if (lib == nullptr) {
            throw std::runtime_error(std::string("Open lib: ") + dlerror());
        }
        return lib;
    }
    void close(void* lib) {
        dlclose(lib);
    }
    std::map<std::string, std::reference_wrapper<AliveTypeBuilder>> type_builders;
    std::map<std::string, std::reference_wrapper<AliveBuilder>> enemy_builders;
    std::map<std::string, void*> libs;
public:
    AliveManager(std::string path = "plugins/Enemy/alive");
    Enemy &build(const std::string &, Dungeon &, size_t, std::pair<size_t, size_t>, size_t, FRACTIONS fraction = FRACTIONS::ENEMY) const;
    std::unique_ptr<EnemyType> build(const std::string &enemy_naming, uint level) const;
    const std::vector<std::string> getAllAliveTypes() const;
    ~AliveManager();
};


#endif //LAB3_ALIVEMANAGER_H
