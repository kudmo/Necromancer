#include <Field/Field.h>
#include "../../include/Exceptions/DungeonExceptions.h"

std::shared_ptr<Item> Field::popUpperItem() {
    std::shared_ptr<Item> temp = std::shared_ptr<Item>(items[items.size() - 1]);
    items.pop_back();
    return temp;
}

void Field::addItem(Item &item) {
    if(!isPassable())
        throw dungeon_errors::invalid_position_error(std::string("This is unpassable field"));
    auto temp = std::shared_ptr<Item>(&item);
    this->items.push_back(temp);
}

const std::vector<std::reference_wrapper<Item>> Field::getItems() const {
    std::vector<std::reference_wrapper<Item>> temp;
    temp.reserve(items.size());
    for (auto & i : items) {
        temp.push_back(std::reference_wrapper<Item>(*i.get()));
    }
    return temp;
}

bool Field::isPassable() const {
    bool coverage_passable = !coverage || coverage->isPassable();
    bool specialization_passable = !specialization || specialization->isPassable();
    return coverage_passable && specialization_passable;
}

/*!
 * @throw dungeon_errors::invalid_position_error if This is unpassable field
 */
void Field::whenEntrance(Entity &e) {
    if (!isPassable())
        throw dungeon_errors::invalid_position_error(std::string("This is unpassable field"));
    if (coverage)
        coverage->effect(e);
}
/*!
 * @throws dungeon_errors::invalid_position_error if This is unpassable field
 */
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
        throw dungeon_errors::invalid_interaction_error(std::string("There are no special element"));

}

//! @todo или вместо сеттеров сделать функцию, которая может только 1 раз поменять nullptr на что-то
void Field::setCoverage(Coverage *coverage) {
    this->coverage.reset(coverage);
}
void  Field::setSpecialization(SpecialElement *specialization) {
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
