#ifndef LAB3_FLOOR_H
#define LAB3_FLOOR_H

#include <vector>
#include <optional>
#include <memory>
#include <unordered_set>
#include <string>
#include <map>
#include <mutex>

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

    std::mutex m_entities;
public:
    Floor(Dungeon& dungeon, size_t number, std::string filename);
    void loadFloor();

    //!@todo возможно лучше weak_ptr
    const std::vector<std::weak_ptr<Entity>> getEntities();
    void unloadFloor();

    size_t getFloorNumber() const {
        return number;
    }
    Dungeon& getDungeon() {return dungeon;}
    /*!
     * @throws dungeon_errors::invalid_position_error if next field going out of bounds
     */
    std::pair<size_t, size_t> getNextByDirection(std::pair<size_t, size_t>, DIRECTIONS);

    /*!
     * @throws dungeon_errors::invalid_position_error if no field with this coordinates
     */
    Field& getByCoord(std::pair<size_t,size_t> coord);
    /*!
     * @throws dungeon_errors::invalid_position_error if no field with this coordinates
     */
    const Field& getByCoord(std::pair<size_t,size_t> coord) const;
    /*!
     * @throws dungeon_errors::invalid_position_error if no field with this coordinates
     */
    Field& getByCoord(size_t X, size_t Y);
    /*!
     * @throws dungeon_errors::invalid_position_error if no field with this coordinates
     */
    const Field& getByCoord(size_t X, size_t Y) const;

    std::pair<size_t, size_t> getSize() const {return std::make_pair<size_t>(floor_map->line_size(),floor_map->line_count());}
    void whenEntrance(Entity& e) {};
    void whenOut(Entity& e) {};

    void summonEntity(const std::shared_ptr<Entity>& e);
    void addEntity(const std::shared_ptr<Entity>& e);
    std::shared_ptr<Entity> removeEntity(Entity& e);

    ~Floor();
};

#endif //LAB3_FLOOR_H
