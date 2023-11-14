#ifndef LAB3_IPOSITION_H
#define LAB3_IPOSITION_H

#include "IPosisionable.h"

class IPosition {
public:
    virtual IPosition & getNextByDirection(DIRECTIONS) = 0;

    //! @brief Данные два метода нужны для ПЕРВИЧНОГО добавления на карту и ОКОНЧАТЕЛЬНОГО удаления с карты
    virtual void appearPositionable(IPositionable&) = 0;
    virtual void disappearPositionable(IPositionable&) = 0;

};
#endif //LAB3_IPOSITION_H
