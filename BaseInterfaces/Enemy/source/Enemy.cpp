#include "../include/Enemy/Enemy.h"

Enemy::Enemy(Floor &f, std::pair<size_t, size_t> coord, EnemyType *type, FRACTIONS fraction) :
        Entity(f, coord, fraction),
        type(type)
{
    if (!type)
        throw enemy_errors::invalid_type_error("type must be not nullptr");

    this->current_hp = type->getMaxHp();
}

std::string Enemy::getNaming() const {
    return type->getNaming();
}

const Entity &Enemy::getTarget() const  {
    return *target;
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