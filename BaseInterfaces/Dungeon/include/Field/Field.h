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

enum class DIRECTIONS {
    //! @todo Прописать направления
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

class Field {
private:
    std::pair<size_t ,size_t> position;

    //! @todo Переделать на нормальные указатели/ссылки + возможность отсутствия значения
    std::unique_ptr<Coverage> coverage;
    std::unique_ptr<SpecialElement> specialization;

    uint essence_count = 0;

    //!@todo поменять на wrapper std::reference_wrapper (<functional>), или std::shared_ptr
    std::vector<Item*> items;
public:
    Field(std::pair<size_t, size_t> position): position(position) {}
//    Field(Floor*f, std::pair<int,int> position): floor(f), position(position) {;}

    void setCoverage(Coverage *);
    void setSpecialization(SpecialElement *);

    uint collectEssence();
    void addEssence(uint);

    void addItem(Item &);
    Item& popUpperItem();
    bool isPassable() const;

    //! @todo А так ли этот метод нужен вообще?
    //Field &getNextByDirection(DIRECTIONS);

    void whenEntrance(Entity&);
    void whenStay(Entity&);
    void whenOut(Entity&);
    void specialInteract(ISmartInteractor&);
    const std::vector<Item*> getItems() const;

    ~Field() = default;
};
#endif //LAB3_FIELD_H
