#ifndef LAB3_FIELD_H
#define LAB3_FIELD_H

#include <utility>
#include <vector>
#include <memory>
#include <cstdlib>

class ISmartInteractor;
class Coverage;
class SpecialElement;

class Entity;
class Item;

class Floor;

enum class DIRECTIONS {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

class Field {
private:
    std::unique_ptr<Coverage> coverage;
    std::unique_ptr<SpecialElement> specialization;

    uint essence_count = 0;
    std::vector<std::shared_ptr<Item>> items;
public:
    void setCoverage(Coverage *);
    void setSpecialization(SpecialElement *);

    bool isPassable() const;
    void specialInteract(ISmartInteractor&);

    uint collectEssence();
    void addEssence(uint);

    void addItem(Item &);
    std::shared_ptr<Item> popUpperItem();
    std::shared_ptr<Item> removeItem(Item&);

    const std::vector<std::reference_wrapper<Item>> getItems() const;

    void whenEntrance(Entity&);
    void whenStay(Entity&);
    void whenOut(Entity&);

    ~Field() = default;
};
#endif //LAB3_FIELD_H
