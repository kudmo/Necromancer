#include <fstream>
#include <jsoncpp/json/json.h>

#include "../../include/Dungeon/Dungeon.h"

Dungeon::Dungeon(std::string filename) {
    loadDungeon(filename);
}

// {"count","floors" : [{"file"}]}
void Dungeon::loadDungeon(std::string filename) {
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
        auto curr = new Floor(*this, i, input["floors"][i]["file"].asString());
        all_floors.push_back(curr);
    }

    this->file = filename;
    input.clear();
    f.close();
}


Floor *Dungeon::floorByNumber(size_t number) {
    return all_floors[number];
}