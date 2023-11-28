#include <fstream>
#include <errno.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <cstring>

#include <Floor/Floor.h>
#include <Field/Field.h>
#include <Dungeon/Dungeon.h>
#include <Entity/Entity.h>

#include <Magma/Magma.h>
#include <Wall/Wall.h>
#include <Door/Door.h>
#include <Ladder/Ladder.h>

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
        throw std::runtime_error(std::string("File error: ") + strerror(errno));
    Json::Value input;
    f >> input;

    if (f.bad() || f.eof()) {
        f.close();
        throw std::runtime_error(std::string("File reading error: ") + strerror(errno));
    }

    // чтение размеров
    size_t size_x, size_y;
    size_x = input["size_x"].asLargestUInt();
    size_y = input["size_x"].asLargestUInt();

    this->floor_map = new Matrix<Field*>(size_x, size_y);
//    this->floor_map->at(0,0) = nullptr;//= new Field();
    // заполнение карты
    for (size_t y = 0; y < size_y; y++) {
        for (size_t x = 0; x < size_x; x++) {
            uint i_ = static_cast<uint>(y);
            uint j_ = static_cast<uint>(x);
            bool have_improvement = input["map"][i_][j_]["have_improvement"].asBool();
            Field *curr;
            if (!have_improvement) {
                //! @todo или стену тут создавать.... или через optional
                curr = nullptr;
            } else {
                curr = new Field();

                // покрытие
                std::string coverage = input["map"][i_][j_]["coverage"].asString();
                if (coverage == "magma") {
                    curr->setCoverage(new Magma());
                }

                // специальный элемент
                // сначала тип - потом параметы
                std::string specialization = input["map"][i_][j_]["specialization"]["type"].asString();
                if (specialization == "wall") {
                    curr->setSpecialization(new Wall());
                } else if (specialization == "door") {
                    curr->setSpecialization(new Door());
                } else if (specialization == "ladder") {
                    size_t level = input["map"][i_][j_]["specialization"]["level_purpose"].asLargestUInt();
                    auto ladder = new Ladder(this->dungeon, this->number, level);
                    curr->setSpecialization(ladder);
                }

                // количество эссенции
                size_t essence_count = input["map"][i_][j_]["essence_count"].asLargestUInt();
                curr->addEssence(essence_count);

                //! @todo предметы?
            }
            this->floor_map->at(x, y) = curr;
        }
    }
    this->entrance_point = std::pair<size_t,size_t>(input["entrance"]["x"].asLargestUInt(), input["entrance"]["y"].asLargestUInt());
    //! @todo спавн сущностей
    size_t enemy_count = input["enemies_count"].asLargestUInt();

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
    //!@todo прописать что происходит при удалении игрока (остановка игры и тп)
    auto temp = std::shared_ptr<Entity>(entities.at(&e));
    entities.erase(&e);
    return temp;
}

Floor::~Floor() {
    if (floor_map) {
        for (auto i = floor_map->begin(); i <= floor_map->end(); ++i) {
            delete *i;
        }
    }
    delete floor_map;
}

const Field &Floor::getByCoord(std::pair<size_t, size_t> coord) const {
    return *floor_map->at(coord.first,coord.second);
}

Field &Floor::getByCoord(std::pair<size_t, size_t> coord) {
    return *floor_map->at(coord.first,coord.second);

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
                    std::cout << floor_map->at(j, i)->asStr() << " ";
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

