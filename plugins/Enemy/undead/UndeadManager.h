#ifndef LAB3_UNDEADMANAGER_H
#define LAB3_UNDEADMANAGER_H


#include <string>
#include <vector>
#include <map>
#include <memory>
#include <dlfcn.h>
#include <filesystem>

#include "Enemy/Enemy.h"
#include "Dungeon/Dungeon.h"
#include "Undead/Undead.h"
#include "UndeadType/UndeadType.h"

namespace fs = std::filesystem;

class UndeadManager {
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

    std::map<std::string, std::reference_wrapper<UndeadTypeBuilder>> type_builders;
    std::map<std::string, std::reference_wrapper<UndeadBuilder>> enemy_builders;
    std::map<std::string, void*> libs;
public:
    UndeadManager(std::string path = "plugins/Enemy/undead");
    Enemy& build(const std::string &, Dungeon &, size_t f, std::pair<size_t,size_t> coord, uint level, std::unique_ptr<AliveType> &&dead, FRACTIONS fraction = FRACTIONS::ENEMY) const;
    std::unique_ptr<EnemyType> build(const std::string &enemy_naming, uint level, std::unique_ptr<AliveType>&& who) const;
    const std::vector<std::string> getAllUndeadTypes() const;
    ~UndeadManager();
};


#endif //LAB3_UNDEADMANAGER_H
