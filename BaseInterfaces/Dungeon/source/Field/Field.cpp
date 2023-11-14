#include <exception>
#include "../../include/Field/Field.h"
#include "../../include/Exceptions/DungeonExceptions.h"

Item &Field::popUpperItem() {
    auto temp = items[items.size() - 1];
    items.pop_back();
    return temp;
}

void Field::addItem(Item &item) {
    this->items.push_back(&item);
}

const std::vector<Item*> Field::getItems() const {
    return items;
}

bool Field::isPassable() const {
    bool coverage_passable = !coverage || coverage->isPassable();
    bool specialization_passable = !specialization || specialization->isPassable();
    return coverage_passable && specialization_passable;
}

void Field::whenEntrance(Entity &e) {
    if (!isPassable())
        throw dungeon_errors::invalid_position_error(std::string("This is unpassable field"));
    if (coverage)
        coverage->effect(e);
}

void Field::whenStay(Entity &e) {
    if (!isPassable())
        throw dungeon_errors::invalid_position_error(std::string("This is unpassable field"));
    if (coverage)
        coverage->effect(e);
}

void Field::whenOut(Entity &e) {
    if(coverage) coverage->effect(e);
}

void Field::specialInteract(ISmartInteractor &e) {
    if (specialization)
        specialization->interact(e);
    else
        throw dungeon_errors::invalid_interaction_error(std::string("There are no special element"))

}

// или вместо сеттеров сделать функцию, которая может только 1 раз поменять nullptr на что-то
void Field::setCoverage(Coverage *coverage) {
    //! @todo Возможно это надо делать через перемещающий конструктор
    this->coverage.reset(coverage);
}
void  Field::setSpecialization(SpecialElement *specialization) {
    //! @todo Возможно это надо делать через перемещающий конструктор
    this->specialization.reset(specialization);
}

uint Field::collectEssence() {
    uint temp = essence_count;
    essence_count = 0;
    return temp;
}

void Field::addEssence(uint count) {
    essence_count += count;
}
