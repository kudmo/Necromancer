#ifndef LAB3_DEADBODY_H
#define LAB3_DEADBODY_H

#include <utility>

#include <Item/Item.h>

class AliveType;

class DeadBody : public Item {
private:
    std::unique_ptr<AliveType> who_it_was = nullptr;
public:
    DeadBody( Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<AliveType>&& a);

    const AliveType &getType() const;

    const std::string getInfo() const override;

    std::unique_ptr<AliveType> takeBody();
};

#endif //LAB3_DEADBODY_H
