#ifndef LAB3_DEADBODY_H
#define LAB3_DEADBODY_H

#include <utility>

#include <Item/Item.h>

class AliveType;

class DeadBody : public Item {
private:
    AliveType* who_it_was = nullptr;
public:
    DeadBody( Floor& f, std::pair<size_t,size_t> coord, AliveType* a);

    const AliveType &getType() const;
    AliveType *takeBody();

    ~DeadBody() override;
};

#endif //LAB3_DEADBODY_H
