#ifndef LAB3_DUNGEON_H
#define LAB3_DUNGEON_H

#include <utility>
#include <vector>
#include <string>
#include <memory>

class Floor;
class Entity;

class IUpdatable{

};

class Dungeon {
private:
    size_t current_level = 0;

    std::vector<std::shared_ptr<Floor>> all_floors;
    std::string file;
public:
    explicit Dungeon(std::string filename);

    Floor &getCurrentFloor() {return getFloorByNumber(getCurrentFloorNumber());}
    Floor &getFloorByNumber(size_t number);
    size_t getCurrentFloorNumber() const {return current_level;}
    void loadDungeon();
//    void unloadDungeon();

    void move(size_t from, size_t to, Entity& e);
    void move(Floor& from, Floor &to, Entity& e);

    void Update();

    ~Dungeon() = default;
};
#endif //LAB3_DUNGEON_H
