#ifndef LAB3_FIELD_H
#define LAB3_FIELD_H

#include <utility>
#include <vector>

#include "../Floor/Floor.h"
#include "../Coverage/Coverage.h"
#include "../SpecialElement/SpecialElement.h"
#include "../../../Items/include/Item/Item.h"
#include "../../../Entity/include/Entity/Entity.h"

enum class DIRECTIONS {};

class Field {
private:
    Floor *floor;
    std::pair<int,int> position;
    Coverage *coverage;
    SpecialElement *specialization;
    uint essence_count;
    std::vector<Item*> items;
public:
    Field();
    bool isPassable() const;
    Field *getNextByDirection(DIRECTIONS);
    void whenEntrance(Entity&);
    void whenStay(Entity&);
    void whenOut(Entity&);
    void specialInteract(ISmartInteractor&);
    Item *getUpperItem();
};
#endif //LAB3_FIELD_H
