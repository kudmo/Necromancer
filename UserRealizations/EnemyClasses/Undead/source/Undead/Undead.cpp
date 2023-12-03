#include "../../include/Undead/Undead.h"

Undead::Undead(Floor &f, std::pair<size_t, size_t> coord, UndeadType *type, FRACTIONS fraction) : Enemy(f, coord, type, fraction) {}

void Undead::die() {
    Enemy::die();
}

const std::string Undead::getFullInfo() const {
    std::string res = "{";

    res += "\"level_info\" : ";
    res += "{";
        res += "\"level\" : ";
            res += std::to_string(type->getLevel()) + ", ";

        res += "\"coefficient\" : ";
            res += std::to_string(dynamic_cast<UndeadType*>(type)->getCoefficient());
    res += "}, ";

    res += "\"characteristics\" : ";
    res += "{";
        res += "\"hp\" : ";
        res += "{";
            res += "\"max\" : " + std::to_string(getMaxHp()) + ", ";
            res += "\"current\" : " + std::to_string(getCurrentHp());
        res += "}, ";

        res += "\"damage\" : ";
            res += std::to_string(getDamage());
    res += "}";

    res += "}";
    return res;
}
