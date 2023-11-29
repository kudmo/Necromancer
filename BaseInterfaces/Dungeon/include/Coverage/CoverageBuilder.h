#ifndef LAB3_COVERAGEBUILDER_H
#define LAB3_COVERAGEBUILDER_H
#include <Coverage/Coverage.h>

class Dungeon;

class CoverageBuilder {
public:
    virtual const Coverage &build(Dungeon&, size_t floor_number, std::pair<size_t, size_t> coordinates) = 0;
};
#endif //LAB3_COVERAGEBUILDER_H
