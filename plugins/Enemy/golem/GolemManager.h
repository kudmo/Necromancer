#ifndef LAB3_GOLEMMANAGER_H
#define LAB3_GOLEMMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <dlfcn.h>
#include <filesystem>

#include "Enemy/Enemy.h"
#include "Dungeon/Dungeon.h"
#include "Golem/Golem.h"
#include "GolemType/GolemType.h"


namespace fs = std::filesystem;

class GolemManager {
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
    std::map<std::string, std::reference_wrapper<GolemTypeBuilder>> type_builders;
    std::map<std::string, std::reference_wrapper<GolemBuilder>> enemy_builders;
    std::map<std::string, void*> libs;
public:
    GolemManager(std::string path = "plugins/Enemy/golem");
    Enemy &build(const std::string &, Dungeon &, size_t, std::pair<size_t, size_t>, size_t, FRACTIONS fraction = FRACTIONS::ENEMY) const;
    std::unique_ptr<EnemyType> build(const std::string &enemy_naming, uint level) const;
    const std::vector<std::string> getAllGolemTypes() const;
    ~GolemManager();
};


#endif //LAB3_GOLEMMANAGER_H
