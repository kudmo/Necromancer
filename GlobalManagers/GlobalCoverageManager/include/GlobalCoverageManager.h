#ifndef LAB3_GLOBALCOVERAGEMANAGER_H
#define LAB3_GLOBALCOVERAGEMANAGER_H

#include <string>
#include <cstdlib>
#include <utility>

#include "Coverage/Coverage.h"
#include "Coverage/CoverageBuilder.h"

class GlobalCoverageManager {
public:
    static const Coverage &build(const std::string &naming, Dungeon &, size_t level, std::pair<size_t, size_t> coordinates);
};


#endif //LAB3_GLOBALCOVERAGEMANAGER_H
