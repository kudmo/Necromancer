#ifndef LAB3_DUNGEON_H
#define LAB3_DUNGEON_H

#include <utility>
#include <map>
#include <vector>
#include <string>
#include <functional>

#include "../Floor/Floor.h"
class IUpdatable{};

class Dungeon {
private:
//    std::map<IUpdatable*,Floor*> udating;
    size_t current_level = 0;

    //!@todo поменять на wrapper std::reference_wrapper (<functional>)
    std::vector<Floor*> all_floors;
//    std::vector<std::reference_wrapper<Floor>> floors;
    std::string file;
    void loadDungeon(std::string filename);
public:
    Dungeon(std::string filename);
    Floor *floorByNumber(size_t number);
    void addUpdatable(IUpdatable&);

    void Update();

    ~Dungeon() = default;
};
#endif //LAB3_DUNGEON_H
