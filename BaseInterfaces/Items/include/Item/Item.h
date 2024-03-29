#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

#include <Object/Object.h>
#include <utility>
#include <cstdlib>

class Floor;

class Item : public Object {
public:
    Item(Floor& f, std::pair<size_t,size_t> coord);
};
#endif // LAB3_ITEM_H
