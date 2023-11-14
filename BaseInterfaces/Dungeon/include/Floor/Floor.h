#ifndef LAB3_FLOOR_H
#define LAB3_FLOOR_H

#include <vector>
#include <vector>

#include "Matrix/Matrix.h"
#include "../Field/Field.h"
#include "../Dungeon/Dungeon.h"

#include "../../../Entity/include/Entity/Entity.h"

class Floor {
private:
    std::weak_ptr<Dungeon> dungeon;
    size_t number;

    Matrix<Field*> floor_map;
    //!@todo поменять на wrapper std::reference_wrapper (<functional>, или на std::shared_ptr
    std::vector<Entity*> entities;
    //    std::vector<std::reference_wrapper<Entity>> entities;

    //! @todo тут возможно ссылка
    Field *entrance_point;
    std::string file;
public:
    Floor(Dungeon &, uint number, std::string filename);
    void loadFloor();

    const std::vector<Entity*> getEntities() const;

    void unloadFloor();

    size_t getFloorNumber() const {
        return number;
    }
    Floor *getNextFloor();
    Floor *getPreviousFloor();

    Field* getNextByDirection(Field&, DIRECTIONS) const;

    void whenEntrance(Entity& e);
    void whenOut(Entity& e);

    void addEntity(Entity& e) {
        whenEntrance(e);
        entrance_point->whenEntrance(e);
        e.setPosition(entrance_point);
        //! @todo Добавить в список
        entities.push_back(&e);
    };
    //! @todo возможно нужно бы по указателю передавать
    void removeEntity(Entity& e) {
        whenOut(e);
        //! @todo Удалить из списка
        //! @todo Удалить из памяти
        delete &e;
    }
    ~Floor() = default;
};

#endif //LAB3_FLOOR_H
