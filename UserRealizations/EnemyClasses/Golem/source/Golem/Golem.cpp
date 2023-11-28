#include "../../include/Golem/Golem.h"

Golem::Golem(Floor &f, std::pair<size_t, size_t> coord, GolemType *type, FRACTIONS fraction) : Enemy(f, coord, type,fraction) {}

uint Golem::damaged(IAttacker &attacker, uint damage) {
    srand(time(0));
    uint p = abs(rand()) % 100;
    if (p > getIgnoringProbability()) {
        Enemy::damaged(attacker, damage);
    }
}

void Golem::die() {
    Enemy::die();
}
