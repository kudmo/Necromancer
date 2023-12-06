#ifndef LAB3_FLOOR_H
#define LAB3_FLOOR_H

#include <vector>
#include <optional>
#include <memory>
#include <unordered_set>
#include <string>
#include <map>


#include <Matrix.h>


class Dungeon;
class Field;
enum class DIRECTIONS;

class Entity;

class Floor {
private:
    Dungeon& dungeon;
    size_t number;

    Matrix<Field*> *floor_map;
    std::pair<size_t,size_t> entrance_point;

    std::map<Entity*, std::shared_ptr<Entity>> entities;

    std::string file;
public:
    Floor(Dungeon& dungeon, size_t number, std::string filename);
    void loadFloor();

    //!@todo возможно лучше weak_ptr
    const std::vector<Entity*> getEntities() const;
    void unloadFloor();

    size_t getFloorNumber() const {
        return number;
    }

    std::pair<size_t, size_t> getNextByDirection(std::pair<size_t, size_t>, DIRECTIONS);

    Field& getByCoord(std::pair<size_t,size_t> coord);
    const Field& getByCoord(std::pair<size_t,size_t> coord) const;

    Field& getByCoord(size_t X, size_t Y);
    const Field& getByCoord(size_t X, size_t Y) const;

    std::pair<size_t, size_t> getSize() const {return std::make_pair<size_t>(floor_map->line_size(),floor_map->line_count());}
    void whenEntrance(Entity& e) {};
    void whenOut(Entity& e) {};

/*    void summonEntity(Entity& e) {
        whenEntrance(e);
        getByCoord(e.getCoordinates()).whenEntrance(e);
        e.setFloor(*this);

        auto temp = std::shared_ptr<Entity>(&e);
        entities.emplace(&e, temp);
    }
    void addEntity(Entity& e){
        whenEntrance(e);
        getByCoord(entrance_point).whenEntrance(e);

        e.setFloor(*this);
        e.setCoordinates(entrance_point);

        auto temp = std::shared_ptr<Entity>(&e);
        entities.emplace(&e, temp);
    }*/

    void summonEntity(const std::shared_ptr<Entity>& e);
    void addEntity(const std::shared_ptr<Entity>& e);
    std::shared_ptr<Entity> removeEntity(Entity& e);
    void print();
    ~Floor();
};

#endif //LAB3_FLOOR_H
