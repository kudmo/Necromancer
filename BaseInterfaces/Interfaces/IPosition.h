#ifndef LAB3_IPOSITION_H
#define LAB3_IPOSITION_H

#include "IPosisionable.h"

class IPosition {
public:
    virtual IPosition & getNextByDirection(DIRECTIONS) = 0;

    //! @brief Данные два метода нужны для ПЕРВИЧНОГО добавления на карту и ОКОНЧАТЕЛЬНОГО удаления с карты
    virtual void addPositionable(IPositionable& obj) = 0;
    virtual void removePositionable(IPositionable& obj) = 0;

    virtual void moveFromPositionToPosition(IPosition& from, IPosition& to, IPositionable& obj) = 0;
};
#endif //LAB3_IPOSITION_H
