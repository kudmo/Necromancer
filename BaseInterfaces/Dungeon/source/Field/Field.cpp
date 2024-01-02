#include <Field/Field.h>
#include <Floor/Floor.h>

#include <Coverage/Coverage.h>
#include <SpecialElement/SpecialElement.h>
#include <Item/Item.h>
#include <Entity/Entity.h>
#include <Exceptions/DungeonExceptions.h>


#include "GlobalCoverageManager.h"
#include <Player/Player.h>

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
        throw dungeon_errors::invalid_position_error(std::string("This is unpassable field: entrance"));
}
/*!
 * @throws dungeon_errors::invalid_position_error if This is unpassable field
 */
void Field::whenStay(Entity &e) {
    if (!isPassable())
        throw dungeon_errors::invalid_position_error(std::string("This is unpassable field: stay"));
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


std::shared_ptr<Item> Field::removeItem(Item &item) {
    for (auto i = items.begin(); i < items.end(); ++i) {
        if (&item == i->get()) {
            std::shared_ptr<Item>temp(*i);
            items.erase(i);
            return temp;
        }
    }
    throw dungeon_errors::dungeon_exception("No item");
}
//        {
//          "have_improvement": true,
//          "coverage": {
//            "type": "no"
//          },
//          "specialization": {
//            "type": "wall"
//          },
//          "items_info": {"items_count" : 0,  "items" : []},
//          "essence_count": 0
//        },
std::string Field::getInfo() const {
    std::string res;
    res += "{";
        res += R"("coverage" : )" + ((coverage)? coverage->getInfo() : std::string(R"({"type" : "no"})")) + ", ";
        res += R"("specialization" : )" + ((specialization)? specialization->getInfo() : std::string(R"({"type" : "no"})")) + ", ";
        res += R"("essence_count" : )" + std::to_string(essence_count) + ", ";
        res += R"("items_info": {"items_count" : )" + std::to_string(items.size()) + ", ";
        res += R"("items" : [)";
        size_t s = items.size(), c = 0;
        for (auto &i : items) {
            res += i->getInfo();
            if (c < s - 1)
                res += ", ";
            ++c;
        }
        res += "]}";
    res += "}";
    return res;
}
