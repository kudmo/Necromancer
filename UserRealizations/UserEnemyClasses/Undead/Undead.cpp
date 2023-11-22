#include "Undead.h"

Undead::Undead(Floor &f, std::pair<size_t, size_t> coord, UndeadType *type, FRACTIONS fraction) : Enemy(f, coord, type, fraction) {}

void Undead::die() {
    Enemy::die();
}
