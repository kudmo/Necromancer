#include <Alive/Alive.h>
#include <DeadBody/DeadBody.h>

Alive::Alive(Floor &f, std::pair<size_t, size_t> coord, AliveType *type, FRACTIONS fraction) : Enemy(f, coord, type, fraction) {}

void Alive::die()  {
    Field& position = this->getPosition();
    auto body = new DeadBody(getFloor(), getCoordinates(), dynamic_cast<AliveType*>(this->type));
    this->type = nullptr;
    position.addItem(*body);
    Enemy::die();
}

const std::string Alive::getInfo() const {
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
