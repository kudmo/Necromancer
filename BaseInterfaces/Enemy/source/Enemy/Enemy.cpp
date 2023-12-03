#include <Enemy/Enemy.h>
#include <SubSkill/SubSkill.h>
#include <EnemyType/EnemyType.h>
#include <IExperienceCollector.h>

Enemy::Enemy(Floor &f, std::pair<size_t, size_t> coord, EnemyType *type, FRACTIONS fraction) :
        Entity(f, coord, fraction),
        type(type)
{
    if (!type)
        throw enemy_errors::invalid_type_error("type must be not nullptr");

    this->current_hp = type->getMaxHp();
    this->skill = nullptr;
}

Enemy::Enemy(Floor &f, std::pair<size_t, size_t> coord, EnemyType *type, FRACTIONS fraction, SubSkill& skill)
        : Entity(f, coord, fraction), type(type) {
    this->current_hp = type->getMaxHp();
    this->skill = &skill;
}

Enemy::~Enemy() {
    delete type;
    delete skill;
}
const std::string Enemy::getNaming() const {
    return type->getNaming();
}
uint Enemy::getLevel() const {
    return type->getLevel();
}

uint Enemy::getMaxHp() const {
    return type->getMaxHp();
}

uint Enemy::getCurrentHp() const {
    return current_hp;
}

uint Enemy::getDamage() const  {
    return type->getDamage();
}

uint Enemy::getExperienceCount() const {
    return type->getExperienceCount();
}

const Entity &Enemy::getTarget() const  {
    return *target;
}
void Enemy::setTarget(Entity &e) {
    this->target = &e;
}

uint Enemy::damaged(IAttacker &attacker, uint damage)  {
    auto r_damage = std::min(damage, current_hp);
    current_hp -= r_damage;
    if (current_hp == 0) {
        IExperienceCollector *temp = dynamic_cast<IExperienceCollector*>(&attacker);
        if (temp)
            temp->collectExperience(getExperienceCount());
        die();
    }
    return r_damage;
}

void Enemy::useSkill(Object &target) {
    if (!skill)
        throw enemy_errors::invalid_skill_error("No skill to use");
    skill->skill(getLevel(), *this, target);
}

void Enemy::scanTerritory() {

}

const std::string Enemy::getInfo() const {
    std::string res = "{";
    res += "\"type\" : \"" + getType() + "\", ";
    res += "\"naming\" : \"" + getNaming() + "\", ";
    res += "\"level\" : " + std::to_string(getLevel()) + ", ";
    res += "\"coord\" : ";
    res += std::string("{") + "\"x\" : " + std::to_string(getCoordinates().first) + ", ";
    res += "\"y\" : " + std::to_string(getCoordinates().second) + "}, ";
    res += "\"fraction\" : " + ("\"" + convertFractionToStr(getFraction()) + "\"");
    res += "}";
    return res;
}





