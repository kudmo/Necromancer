#include <algorithm>

#include "Player.h"

Player::Player(Floor &f, std::pair<size_t, size_t> coord) : Entity(f,coord,FRACTIONS::PLAYER) {}

uint Player::damaged(IAttacker&, uint d) {
    auto r_damage = std::min(d, current_hp);
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

uint Player::getCurrentControlledCount() const {
    return current_undead_count;
}

uint Player::getMaxUndeadCount() const {
    return max_undead_count;
}

void Player::addNewControlledUndead(Undead &undead)  {
    if (undead.getFraction() != this->getFraction())
        throw player_errors::player_exception("Can't control undead from other fraction");

    if (current_undead_count == max_undead_count)
        throw player_errors::player_exception("Max controlling count overflow");
    current_undead_count += 1;
}

uint Player::getDamage() const {
    return damage;
}
uint Player::getMaxHp() const {
    return max_hp;
}
uint Player::getCurrentHp() const {
    return current_hp;
}

void Player::upgradeLevel() {
    level += 1;
    skill_points += 1;

    max_hp = calculateMaxHP();
    damage = calculateDamage();
    max_mana_count = calculateMaxMP();
    max_undead_count = calculateMaxUndeadCount();
}

void Player::collectEssence(uint count) {
    this->essence_count += count;
}

void Player::upgradeSkill(std::string name) {
    if (skill_points == 0)
        throw player_errors::invalid_upgrade_error("No enough skill points");
    skills.upgradeSkill(name);
    skill_points -= 1;
}

void Player::useSkill(std::string name , Object &target) {
    skills.useSkill(name, *this, target);
}

void Player::smartInteract(Field &f) {
    f.specialInteract(*this);
}