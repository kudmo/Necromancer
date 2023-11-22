#include "GolemType.h"

GolemType::GolemType(uint level) : EnemyType(level) {}

uint GolemType::getIgnoringProbability() const {
    return calculateIgnoringProbability(getLevel());
}