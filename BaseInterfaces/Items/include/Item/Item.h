#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

#include "../../../Object/include/Object/Object.h"

class Item : public Object {
public:
    Item(Floor& f, std::pair<size_t,size_t> coord): Object(f, coord) {}
};
#endif // LAB3_ITEM_H
