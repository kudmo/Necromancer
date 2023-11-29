#ifndef LAB3_SPECIALELEMENTBUILDER_H
#define LAB3_SPECIALELEMENTBUILDER_H

#include <SpecialElement/SpecialElement.h>
class Dungeon;

class SpecialElementBuilder {
public:
    virtual const SpecialElement& build(Dungeon&, size_t floor_number, std::pair<size_t, size_t> coordinates) = 0;
};

#endif //LAB3_SPECIALELEMENTBUILDER_H
