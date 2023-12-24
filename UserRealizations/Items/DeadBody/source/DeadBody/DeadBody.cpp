#include <DeadBody/DeadBody.h>
#include <AliveType/AliveType.h>
#include "Exceptions/EnemyExceptions.h"

DeadBody::DeadBody(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<AliveType>&& a) : Item(f, coord), who_it_was(std::move(a)) {
    if (who_it_was == nullptr)
        throw enemy_errors::invalid_type_error("type must be not nullptr");

}

const AliveType &DeadBody::getType() const {
    return *who_it_was;
}

std::unique_ptr<AliveType> DeadBody::takeBody()  {
    return std::move(who_it_was);
}


const std::string DeadBody::getInfo() const {
    std::string res =R"({"naming" : "dead_body", )";
    res += "\"type\" : " + ( "\"" + who_it_was->getNaming() + "\"");
    res += "}";
    return res;
}

const std::string DeadBody::getNaming() const {
    return "dead_body : " + who_it_was->getNaming();
}

const std::string DeadBody::getFullInfo() const {
    std::string res = R"({"naming" : "dead_body", )";
    res += "\"type\" : " + ( "\"" + who_it_was->getNaming() + "\"") + ", ";

    res += "\"position\" : ";
    res += "{";
        res += "\"x\" : " + std::to_string(getCoordinates().first) + ", ";
        res += "\"y\" : " + std::to_string(getCoordinates().second);
    res += "}s";

    res += "}";
    return res;
}
