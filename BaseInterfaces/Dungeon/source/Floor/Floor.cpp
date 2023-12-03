#include <fstream>
#include <errno.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <cstring>
#include <iostream>

#include <Floor/Floor.h>
#include <Field/Field.h>
#include <Dungeon/Dungeon.h>
#include <Entity/Entity.h>

#include "GlobalSpecialElementManager.h"
#include "GlobalCoverageManager.h"
#include "GlobalEnemyManager.h"

Floor::Floor(Dungeon &dungeon, size_t number, std::string filename) : dungeon(dungeon) {
    this->number = number;
    this->file = std::move(filename);
    floor_map = nullptr;
}

/*
 * {"size_x", "size_y", "map" : []}
 * field - {"have_improvement"} | {"coverage", "specialization",  "items", "essence_count"}
 */
void Floor::loadFloor() {
    std::ifstream f(this->file);

    if (!f)
        throw std::runtime_error(std::string("Error by loading floor: File error: ") + strerror(errno));
    Json::Value input;
    f >> input;

    if (f.bad() || f.eof()) {
        f.close();
        throw std::runtime_error(std::string("File reading error: ") + strerror(errno));
    }
    // Reading level info
    auto levelInfo = input["level_map"];
    // Reading size of map
    size_t size_x, size_y;
    auto levelSize = levelInfo["size"];
    size_x = levelSize["x"].asLargestUInt();
    size_y = levelSize["y"].asLargestUInt();

    this->floor_map = new Matrix<Field*>(size_x, size_y);

    // Map filling
    auto levelMap = levelInfo["map"];
    for (size_t y = 0; y < size_y; y++) {
        for (size_t x = 0; x < size_x; x++) {
            uint i_ = static_cast<uint>(y);
            uint j_ = static_cast<uint>(x);
            auto currentCell = levelMap[i_][j_];

            bool have_improvement = currentCell["have_improvement"].asBool();
            Field *curr;
            if (!have_improvement) {
                curr = nullptr;
                this->floor_map->at(x, y) = curr;
            } else {
                curr = new Field();
                this->floor_map->at(x, y) = curr;

                // Coverage
                auto coverageInfo = currentCell["coverage"];
                auto coverage = coverageInfo["type"].asString();
                if (coverage != "no")
                    GlobalCoverageManager::build(coverage,
                                                 this->dungeon,
                                                 this->number,
                                                 std::pair<size_t,size_t>(x,y));


                // Special Element
                auto specializationInfo = currentCell["specialization"];
                auto specialization = specializationInfo["type"].asString();
                if (specialization != "no")
                    GlobalSpecialElementManager::build(specialization,
                                                       this->dungeon,
                                                       this->number,
                                                       std::pair<size_t,size_t>(x,y));

                // Essence
                size_t essence_count = currentCell["essence_count"].asLargestUInt();
                curr->addEssence(essence_count);
            }
        }
    }


    // Entrance setting
    auto levelEntrance = levelInfo["entrance"];
    this->entrance_point = std::pair<size_t,size_t>(levelEntrance["x"].asLargestUInt(), levelEntrance["y"].asLargestUInt());


    // Enemies spawning
    auto levelEnemiesInfo = input["enemies_info"];
    uint enemy_count = levelEnemiesInfo["enemies_count"].asLargestUInt();
    for (uint i = 0; i < enemy_count; ++i) {
        auto currentEnemy = levelEnemiesInfo["enemies"][i];

        auto enemy_type = currentEnemy["type"].asString();
        auto enemy_naming = currentEnemy["naming"].asString();
        auto enemy_level = currentEnemy["level"].asLargestUInt();
        auto enemy_coord = std::pair<size_t ,size_t>(currentEnemy["coord"]["x"].asLargestUInt(),
                                                     currentEnemy["coord"]["y"].asLargestUInt());

        try {
            auto enemy_fraction = convertStrToFraction(currentEnemy["fraction"].asString());
            GlobalEnemyManager::build(enemy_type, enemy_naming, dungeon, number, enemy_coord, enemy_level, enemy_fraction);
        } catch (std::exception& e) {
            std::cerr << e.what() <<std::endl;
        }
    }

    input.clear();
    f.close();
}
void Floor::summonEntity(Entity &e) {
    whenEntrance(e);
    getByCoord(e.getCoordinates()).whenEntrance(e);
    e.setFloor(*this);

    auto temp = std::shared_ptr<Entity>(&e);
    entities.emplace(&e, temp);
}
void Floor::addEntity(Entity &e) {
    whenEntrance(e);
    getByCoord(entrance_point).whenEntrance(e);

    e.setFloor(*this);
    e.setCoordinates(entrance_point);

    auto temp = std::shared_ptr<Entity>(&e);
    entities.emplace(&e, temp);
}

std::shared_ptr<Entity> Floor::removeEntity(Entity &e) {
    whenOut(e);
    auto temp = std::shared_ptr<Entity>(entities.at(&e));
    entities.erase(&e);
    return temp;
}

Floor::~Floor() {
    if (floor_map) {
        for (auto i = floor_map->begin(); i < floor_map->end(); ++i) {
            delete *i;
        }
    }
    delete floor_map;
}


Field &Floor::getByCoord(size_t X, size_t Y) {
    return *floor_map->at(X,Y);
}
const Field &Floor::getByCoord(size_t X, size_t Y) const {
    return *floor_map->at(X,Y);
}

Field &Floor::getByCoord(std::pair<size_t, size_t> coord) {
    return getByCoord(coord.first, coord.second);
}
const Field &Floor::getByCoord(std::pair<size_t, size_t> coord) const {
    return getByCoord(coord.first,coord.second);
}



std::pair<size_t, size_t> Floor::getNextByDirection(std::pair<size_t, size_t> coord, DIRECTIONS d) {
    auto res = std::pair<size_t, size_t>(coord);
    switch (d) {
        case DIRECTIONS::UP:
            if (coord.second == 0)
                throw dungeon_errors::invalid_position_error("going out of bounds");
            res = std::pair<size_t, size_t>(coord.first + 0, coord.second - 1);
            break;
        case DIRECTIONS::RIGHT:
            if (coord.first == floor_map->line_size()-1)
                throw dungeon_errors::invalid_position_error("going out of bounds");
            res = std::pair<size_t, size_t>(coord.first + 1, coord.second);
            break;
        case DIRECTIONS::DOWN:
            if (coord.second == floor_map->line_count()-1)
                throw dungeon_errors::invalid_position_error("going out of bounds");
            res = std::pair<size_t, size_t>(coord.first, coord.second + 1);
            break;
        case DIRECTIONS::LEFT:
            if (coord.first == 0)
                throw dungeon_errors::invalid_position_error("going out of bounds");
            res = std::pair<size_t, size_t>(coord.first - 1, coord.second);
            break;

    }
    return res;
}

void Floor::print() {
    if (!floor_map) return;
    for (size_t i = 0; i < floor_map->line_count(); ++i) {
        for (size_t j = 0; j < floor_map->line_size(); ++j) {
            if (floor_map->at(j,i)) {
                bool flag = true;
                for (auto &e : entities) {
                    if (&e.second->getPosition() == floor_map->at(j,i)) {
                        std::cout << "*" << " ";
                        flag = false;
                        break;
                    }
                }
                if (flag) {
//                    std::cout << floor_map->at(j, i)->asStr() << " ";
                }
            } else
                std::cout<< "%"<< " ";
        }
        std::cout<< std::endl;

    }
}

const std::vector<Entity *> Floor::getEntities() const {
    std::vector<Entity *> res;
    res.reserve(entities.size());
    for (auto &i : entities) {
        res.push_back(i.first);
    }
    return res;
}


