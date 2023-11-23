#ifndef LAB3_DUNGEON_H
#define LAB3_DUNGEON_H

#include <utility>
#include <vector>
#include <string>


class Floor;
class Entity;

class IUpdatable{

};

class Dungeon {
private:
    size_t current_level = 0;

    std::vector<Floor> all_floors;

    std::string file;
public:
    Dungeon(std::string filename);

    Floor &floorByNumber(size_t number);

    void loadDungeon();
    void unloadDungeon();

    void move(size_t from, size_t to, Entity& e);
    void move(Floor& from, Floor &to, Entity& e);

    void Update();

    ~Dungeon() = default;
};
#endif //LAB3_DUNGEON_H
