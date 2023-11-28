#ifndef LAB3_LADDER_H
#define LAB3_LADDER_H

#include "SpecialElement/SpecialElement.h"
class Dungeon;

class Ladder : public SpecialElement{
private:
    //!@todo возможно лучше хранить просто номер уровня
    size_t from;
    size_t to;
    Dungeon& dungeon;
public:
    Ladder(Dungeon& d, size_t from, size_t to);
    bool isPassable() override;
    void interact(ISmartInteractor& e) override;
};

class LadderBuilder : public SpecialElementBuilder {
public:
    //! @todo проблемка - лестницу нельзя создать "дефолтно"
    SpecialElement * build() override;
};

#endif //LAB3_LADDER_H
