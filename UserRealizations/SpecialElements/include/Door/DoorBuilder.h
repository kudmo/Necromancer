#ifndef LAB3_DOORBUILDER_H
#define LAB3_DOORBUILDER_H

#include "Door/Door.h"
#include "SpecialElement/SpecialElementBuilder.h"

class DoorBuilder : public SpecialElementBuilder {
public:
    const SpecialElement &build(Dungeon &dungeon, size_t floor_number, std::pair<size_t, size_t> coordinates) override;
};


#endif //LAB3_DOORBUILDER_H
