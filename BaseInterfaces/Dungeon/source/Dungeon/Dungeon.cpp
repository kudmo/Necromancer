#include <fstream>
#include <jsoncpp/json/json.h>
#include <cstring>

#include "../../include/Floor/Floor.h"

Dungeon::Dungeon(std::string filename) {
    this->file = filename;
}

void Dungeon::move(Floor &from, Floor &to, Entity &e) {
    //! @todo обновить обновляемые уровни
    try {
        dynamic_cast<IUpdatable&>(e);
        current_level = to.getFloorNumber();
    } catch (std::bad_cast) {

    }

    auto temp = from.removeEntity(e);
    to.loadFloor();
    to.addEntity(e);
    from.unloadFloor();
}

void Dungeon::move(size_t from, size_t to, Entity &e)  {
    move(all_floors[from], all_floors[to], e);
}


// {"count","floors" : [{"file"}]}
void Dungeon::loadDungeon() {
    auto filename = this->file;
    std::ifstream f(filename);
    if (!f)
        throw std::runtime_error(std::string("File error: ") + strerror(errno));
    Json::Value input;

    f >> input;
    if (f.bad() || f.eof()) {
        f.close();
        throw std::runtime_error(std::string("File reading error: ") + strerror(errno));
    }
    size_t count = input["count"].asLargestUInt();
    all_floors.clear();
    all_floors.reserve(count);

    //!@todo не забыть про исключения на какой-то итерации
    for (int i = 0; i < count; i++) {
        Floor curr = Floor(*this, static_cast<size_t>(i), input["floors"][i]["file"].asString());
        all_floors.push_back(curr);
    }

    this->file = filename;
    input.clear();
    f.close();
}


Floor &Dungeon::floorByNumber(size_t number) {
    return all_floors[number];
}