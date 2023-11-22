#ifndef LAB3_FLOOR_H
#define LAB3_FLOOR_H

#include <vector>
#include <optional>
#include <memory>
#include <unordered_set>
#include <string>
#include <map>

#include "Matrix/Matrix.h"
#include "../Field/Field.h"
#include "../Dungeon/Dungeon.h"

#include "../../../Entity/include/Entity/Entity.h"

class Dungeon;
class Entity;

class Floor {
private:
    Dungeon& dungeon;
    size_t number;

    Matrix<Field*> *floor_map; //< @todo optional
    std::pair<size_t,size_t> entrance_point;

    //!@todo поменять в функциях на std::shared_ptr
    //!@todo а игрок возможно вообще отдельно хранится)))))))))))
    std::map<Entity*, std::shared_ptr<Entity>> entities;

    std::string file;
public:
    Floor(Dungeon& dungeon, size_t number, std::string filename);
    void loadFloor();

    const std::vector<Entity*> getEntities() const;
    void unloadFloor();

    size_t getFloorNumber() const {
        return number;
    }

    //! @todo под вопросом методы)
//    Floor *getNextFloor();
//    Floor *getPreviousFloor();
//    Field& getNextByDirection(Field&, DIRECTIONS);

    std::pair<size_t, size_t> getNextByDirection(std::pair<size_t, size_t>, DIRECTIONS);

    Field& getByCoord(std::pair<size_t,size_t> coord);
    const Field& getByCoord(std::pair<size_t,size_t> coord) const;

    void whenEntrance(Entity& e);
    void whenOut(Entity& e);

    void addEntity(Entity& e);
    std::shared_ptr<Entity> removeEntity(Entity& e);

    ~Floor() = default;
};

#endif //LAB3_FLOOR_H
