#include <fstream>
#include <jsoncpp/json/json.h>
#include <cstring>

#include <Dungeon/Dungeon.h>
#include <Floor/Floor.h>
#include <Entity/Entity.h>
#include <memory>

Dungeon::Dungeon(std::string filename) {
    this->file = filename;
}

void Dungeon::move(Floor &from, Floor &to, Entity &e) {
    //! @todo обновить обновляемые уровни
    try {
        dynamic_cast<IUpdatable&>(e);
        current_level = to.getFloorNumber();
    } catch (std::bad_cast& e) {

    }
    current_level = to.getFloorNumber();
    auto temp = from.removeEntity(e);
    to.loadFloor();
    to.addEntity(temp);
    from.unloadFloor();
}

void Dungeon::move(size_t from, size_t to, Entity &e)  {
    if (to >= all_floors.size()) {
        auto temp = all_floors[from]->removeEntity(e);
        throw dungeon_errors::invalid_floor_error("No floor");
    }
    move(*all_floors[from], *all_floors[to], e);
}


// {"count","floors" : [{"file"}]}
void Dungeon::loadDungeon() {
    auto filename = this->file;
    std::ifstream f(filename);
    if (!f)
        throw std::runtime_error(std::string("Error while loading dungeon: File error: ") + strerror(errno));
    Json::Value input;

    f >> input;
    if (f.bad() || f.eof()) {
        f.close();
        throw std::runtime_error(std::string("File reading error: ") + strerror(errno));
    }
    size_t count = input["count"].asLargestUInt();
    all_floors.clear();
    all_floors.reserve(count);

    try {
        for (uint i = 0; i < count; i++) {
            auto curr = std::make_shared<Floor>(*this, static_cast<size_t>(i), input["floors"][i]["file"].asString());
            all_floors.push_back(curr);
        }
    } catch (...) {
        input.clear();
        f.close();
        throw ;
    }

    this->file = filename;
    input.clear();
    f.close();
}


Floor &Dungeon::getFloorByNumber(size_t number) {
    return *all_floors[number];
}

void Dungeon::Update() {
    auto &curr = getFloorByNumber(current_level);
    auto entities = curr.getEntities();
    for (auto &entity : entities) {
        auto e = entity.lock();
        e->stay();
    }
}
