#ifndef LAB3_GLOBALSPECIALELEMENTMANAGER_H
#define LAB3_GLOBALSPECIALELEMENTMANAGER_H

#include <string>
#include <cstdlib>
#include <utility>

#include "SpecialElement/SpecialElement.h"
#include "SpecialElement/SpecialElementBuilder.h"

class Dungeon;
class GlobalSpecialElementManager {
public:
    static const SpecialElement &build(const std::string &naming, Dungeon &, size_t level, std::pair<size_t, size_t> coordinates);
};

#endif //LAB3_GLOBALSPECIALELEMENTMANAGER_H
