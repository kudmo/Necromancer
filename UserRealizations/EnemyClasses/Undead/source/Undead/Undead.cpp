#include <iostream>
#include <Undead/Undead.h>

Undead::Undead(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<UndeadType>&& type, FRACTIONS fraction) : Enemy(f, coord, std::move(type), fraction) {}

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
            res += std::to_string(getCoefficient());
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

std::unique_ptr<UndeadType> Undead::takeInnerBody() {
    // это костыль!!!!!!!!
    std::unique_ptr<UndeadType> inner_type;
    inner_type.reset(dynamic_cast<UndeadType *>(type.release()));

    this->die();
    return std::move(inner_type);
}

double Undead::getCoefficient() const {
    return dynamic_cast<UndeadType*>(type.get())->getCoefficient();
}
