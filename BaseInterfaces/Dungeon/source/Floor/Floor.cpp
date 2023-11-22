#include <fstream>
#include <errno.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <cstring>

#include "../../include/Floor/Floor.h"
#include "../../../../UserRealosations/UserCoverages/Magma/Magma.h"
#include "../../../../UserRealosations/UserSpecialElements/Wall/Wall.h"
#include "../../../../UserRealosations/UserSpecialElements/Door/Door.h"
#include "../../../../UserRealosations/UserSpecialElements/Ladder/Ladder.h"


Floor::Floor(Dungeon &dungeon, size_t number, std::string filename) : dungeon(dungeon) {
    this->number = number;
    this->file = filename;
}

/*
 * {"size_x", "size_y", "fields" : []}
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

    // заполнение карты
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            bool have_improvement = input["map"][i][j]["have_improvement"].asBool();
            Field *curr;
            if (!have_improvement) {
                //! @todo или стену тут создавать.... или через optional
                curr = nullptr;
            } else {
                curr = new Field();

                // покрытие
                std::string coverage = input["map"][i][j]["coverage"].asString();
                if (coverage == "magma") {
                    curr->setCoverage(new Magma());
                }

                // специальный элемент
                // сначала тип - потом параметы
                std::string specialization = input["map"][i][j]["specialization"]["type"].asString();
                if (specialization == "wall") {
                    curr->setSpecialization(new Wall());
                } else if (specialization == "door") {
                    curr->setSpecialization(new Door());
                } else if (specialization == "ladder") {
                    size_t level = input["map"][i][j]["specialization"]["level_purpose"].asLargestUInt();
                    auto ladder = new Ladder(this->dungeon, this->number, level);
                    curr->setSpecialization(ladder);
                }

                // количество эссенции
                size_t essence_count = input["map"][i][j]["essence_count"].asLargestUInt();
                curr->addEssence(essence_count);

                //! @todo предметы?
            }
            this->floor_map->at(i,j) = curr;
        }
    }
    this->entrance_point = std::pair<size_t,size_t>(input["entrance"]["x"].asLargestUInt(), input["entrance"]["y"].asLargestUInt());

    //! @todo спавн сущностей
    size_t enemy_count = input["enemies_count"].asLargestUInt();

    input.clear();
    f.close();
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

