#ifndef LAB3_LADDERBUILDER_H
#define LAB3_LADDERBUILDER_H

#include <SpecialElement/SpecialElementBuilder.h>

class LadderBuilder : public SpecialElementBuilder {
public:
    const SpecialElement &build(Dungeon &dungeon, size_t floor_number, std::pair<size_t, size_t> coordinates) override;
};

#endif //LAB3_LADDERBUILDER_H
