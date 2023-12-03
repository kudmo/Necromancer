#include "../../include/Golem/Golem.h"

Golem::Golem(Floor &f, std::pair<size_t, size_t> coord, GolemType *type, FRACTIONS fraction) : Enemy(f, coord, type,fraction) {}

uint Golem::damaged(IAttacker &attacker, uint damage) {
    //!@todo дописать игнор урона
    srand(time(0));
    uint p = abs(rand()) % 100;
    if (p > getIgnoringProbability()) {
        Enemy::damaged(attacker, damage);
    }
}

void Golem::die() {
    Enemy::die();
}

const std::string Golem::getFullInfo() const {
    std::string res = "{";

    res += "\"level_info\" : ";
    res += "{";
        res += "\"level\" : ";
            res += std::to_string(type->getLevel());
    res += "}, ";

    res += "\"characteristics\" : ";
    res += "{";
        res += "\"hp\" : ";
        res += "{";
            res += "\"max\" : " + std::to_string(getMaxHp()) + ", ";
            res += "\"current\" : " + std::to_string(getCurrentHp());
        res += "}, ";

        res += "\"damage\" : ";
            res += std::to_string(getDamage()) +", ";

        res += "\"ignoring_probability\" : ";
            res += std::to_string(dynamic_cast<GolemType*>(type)->getIgnoringProbability());
    res += "}";

    res += "}";
    return res;
}
