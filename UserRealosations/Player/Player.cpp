#include <algorithm>

#include "Player.h"

uint Player::damaged(IAttacker&, uint damage) {
    auto r_damage = std::min(damage, current_hp);
    current_hp -= r_damage;
    if (current_hp == 0)
        die();
    return r_damage;
}

uint Player::needExpToUpgrade() const {
    //! @todo функкция подсчёта
    return level*100;
}

void Player::collectExperience(uint exp) {
    experience += exp;
    if (exp == needExpToUpgrade()) {
        upgradeLevel();
        experience = 0;
    }

}

void Player::upgradeLevel() {
    level += 1;
    experience = 0;
    skill_points += 1;
    //! @todo Улучшения характеристик
}

void Player::collectEssence(uint count) {
    this->essence_count += count;
}

void Player::upgradeSkill(std::string name) {
    if (skill_points == 0) {
        //! @todo ошибка
    }
    skills.upgradeSkill(name);
    skill_points -= 1;
}



void Player::useSkill(std::string name , Object &target) {
    skills.useSkill(name, *this, target);
}