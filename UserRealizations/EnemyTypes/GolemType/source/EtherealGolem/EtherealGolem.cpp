#include <EtherealGolem/EtherealGolem.h>

EtherealGolem::EtherealGolem(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<EtherealGolemType>&& type, FRACTIONS fraction) : Golem(f, coord, std::move(type),fraction) {}

uint EtherealGolem::getEssence() const {
    auto t = dynamic_cast<EtherealGolemType*>(type.get());
    return t->getEssenceCount();
}

void EtherealGolem::die() {
    this->getPosition().addEssence(this->getEssence());
    Golem::die();
}

const std::string EtherealGolem::getFullInfo() const {
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
            res += "\"max\" : " + std::to_string(getMaxHP()) + ", ";
            res += "\"current\" : " + std::to_string(getCurrentHP());
        res += "}, ";

        res += "\"damage\" : ";
            res += std::to_string(getDamage()) +", ";

        res += "\"ignoring_probability\" : ";
            res += std::to_string(getIgnoringProbability()) + ", ";

        res += "\"essence_count\" : ";
            res += std::to_string(getEssence());

    res += "}";

    res += "}";
    return res;
}
