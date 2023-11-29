#ifndef LAB3_MAGMABUILDER_H
#define LAB3_MAGMABUILDER_H

#include <Magma/Magma.h>
#include <Coverage/CoverageBuilder.h>

class MagmaBuilder : public CoverageBuilder{
public:
    const Coverage &build(Dungeon &dungeon, size_t floor_number, std::pair<size_t, size_t> coordinates) override;
};


#endif //LAB3_MAGMABUILDER_H
