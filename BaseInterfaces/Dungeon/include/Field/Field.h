#ifndef LAB3_FIELD_H
#define LAB3_FIELD_H

#include <utility>
#include <vector>
#include <memory>

#include "../Floor/Floor.h"
#include "../Coverage/Coverage.h"
#include "../SpecialElement/SpecialElement.h"
#include "../../../Items/include/Item/Item.h"
#include "../../../Entity/include/Entity/Entity.h"

//! @todo Либо это норма - либо костыль

class ISmartInteractor;

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
    const std::vector<std::reference_wrapper<Item>> getItems() const;

    void whenEntrance(Entity&);
    void whenStay(Entity&);
    void whenOut(Entity&);

    ~Field() = default;
};
#endif //LAB3_FIELD_H
