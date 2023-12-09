#include <Alive/Alive.h>
#include <DeadBody/DeadBody.h>
#include "Entity/Entity.h"

Alive::Alive(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<AliveType>&& type, FRACTIONS fraction) : Enemy(f, coord, std::move(type), fraction) {
}

void Alive::die()  {
    Field& position = this->getPosition();

    // это костыль!!!!!!!!
    std::unique_ptr<AliveType> dead_type;
    dead_type.reset(dynamic_cast<AliveType *>(type.release()));
    auto body = new DeadBody(getFloor(), getCoordinates(),std::move(dead_type));

    position.addItem(*body);
    Enemy::die();
}

const std::string Alive::getFullInfo() const {
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
            res += std::to_string(getDamage());
    res += "}";

    res += "}";
    return res;
}
