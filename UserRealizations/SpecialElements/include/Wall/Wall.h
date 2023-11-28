#ifndef LAB3_WALL_H
#define LAB3_WALL_H

#include "SpecialElement/SpecialElement.h"

class Wall : public SpecialElement {
public:
    Wall() = default;
    bool isPassable() override;
    void interact(ISmartInteractor &) override;
};

class WallBuilder : public SpecialElementBuilder {
public:
    //! @todo проблемка - лестницу нельзя создать "дефолтно"
    SpecialElement * build() override;
};
#endif //LAB3_WALL_H
