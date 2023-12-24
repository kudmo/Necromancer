#include <algorithm>
#include <iostream>

#include "Player/Player.h"
#include "GlobalEnemyManager.h"
#include "GlobalSkillManager.h"

Player::Player(Floor &f, std::pair<size_t, size_t> coord) : Entity(f,coord,FRACTIONS::PLAYER) {
    level = 1;
    max_hp = calculateMaxHP();
    current_hp = max_hp;
    damage = calculateDamage();
    max_mana_count = calculateMaxMP();
    current_mana_count = max_mana_count;
    max_undead_count = calculateMaxUndeadCount();
}

Player::Player(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<SkillTable>&& table) : Entity(f,coord,FRACTIONS::PLAYER) {
    level = 1;
    skills = std::move(table);
    max_hp = calculateMaxHP();
    current_hp = max_hp;
    damage = calculateDamage();
    max_mana_count = calculateMaxMP();
    current_mana_count = max_mana_count;
    max_undead_count = calculateMaxUndeadCount();
    try {
        auto e = skills->getAllVariations().at("necromancy")[0];
        auto und = e.substr(e.find("_")+1);
        known_undead_types.push_back(und);
    } catch (std::out_of_range&){}
}

void Player::move() {
    setStateMoving();
    Entity::move();
    collectEssence(getPosition().collectEssence());
}

void Player::attack(IAttackable &target) {
    setStateAttacking();
    Entity::attack(target);
}

void Player::damaged(IAttacker&, uint d) {
    std::scoped_lock lock_1(m_is_target);
    std::scoped_lock lock_2(m_charact);
    if (isDead())
        return;
    setStateDamaged();

    auto r_damage = std::min(d, current_hp);
    current_hp -= r_damage;

    if (current_hp == 0)
        die();
}

uint Player::needExpToUpgrade() const {
    //! @todo функкция подсчёта
    return level*100;
}

void Player::collectExperience(uint exp) {
    std::scoped_lock lock_1(m_is_upgrading);
    std::scoped_lock lock_2(m_charact);
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
uint Player::getMaxHP() const {
    return max_hp;
}

uint Player::getCurrentHP() const {
    return current_hp;
}
uint Player::getMaxMP() const {
    return max_mana_count;
}
uint Player::getCurrentMP() const {
    return current_mana_count;
}

uint Player::getExperience() const {
    return experience;
}

uint Player::getEssenceCount() const {
    return essence_count;
}

uint Player::getSkillPoints() const {
    return skill_points;
}


uint Player::getLevel() const {
    return level;
}


void Player::restoreHP(uint count) {
    current_hp = std::min(current_hp + count, max_hp);
}

void Player::restoreMP(uint count) {
    current_mana_count = std::min(current_mana_count + count, max_mana_count);
}

void Player::upgradeLevel() {
    level += 1;
    skill_points += 1;

    max_hp = calculateMaxHP();
    damage = calculateDamage();
    max_mana_count = calculateMaxMP();
    max_undead_count = calculateMaxUndeadCount();
}

void Player::exploreNewUndeadType(const std::string &undead_type) {
    std::scoped_lock lock(m_is_upgrading);
    for (auto &type : known_undead_types)
        if (undead_type == type)
            throw player_errors::player_exception("This type is already explored");

    if (essence_count < 50)
        throw player_errors::player_exception("Not enough essence");
    auto new_morphism = GlobalSkillManager::buildSubSkill("morphism_" + undead_type);
    auto new_necromancy = GlobalSkillManager::buildSubSkill("necromancy_" + undead_type);
    skills->addSkillVariation("morphism", std::move(new_morphism));
    skills->addSkillVariation("necromancy", std::move(new_necromancy));
    essence_count -= 50;
    known_undead_types.push_back(undead_type);
}


void Player::collectEssence(uint count) {
    this->essence_count += count;
}

void Player::upgradeSkill(const std::string& name) {
    std::scoped_lock lock(m_is_upgrading);
    if (skill_points == 0)
        throw player_errors::invalid_upgrade_error("No enough skill points");
    skills->upgradeSkill(name);
    skill_points -= 1;
}


void Player::checkSkillTarget(const std::string &name, const std::string &variation, Object &target) {
    if (!skills)
        throw player_errors::player_exception("No skill table");
    skills->checkSkillTarget(name,variation,target);
}

void Player::useSkill(const std::string& name, const std::string& variation, Object &target) {
    if (!skills)
        throw player_errors::player_exception("No skill table");

    auto cost = skills->getCost(name, variation, target);
    if (cost > current_mana_count)
        throw player_errors::player_exception("Not enough mana");
    skills->useSkill(name, variation, *this, target);
    setStateSkillUsing();
    current_mana_count -= std::min(cost, current_mana_count);
}


void Player::smartInteract(Field &f) {
    f.specialInteract(*this);
    setStateInteracting();
}

void Player::die() {
    setStateDead();
    Entity::die();
}

const std::string Player::getNaming() const {
    return std::string("Player");
}
std::vector<std::string> Player::getAllSkills() const {
    return skills->getAllSkills();
}

std::vector<std::string> Player::getAllSubSkills() const {
    std::vector<std::string > res;
    for (auto& i : skills->getAllVariations()) {
        for (auto &j : i.second) {
            res.push_back(j);
        }
    }
    return res;
}


//!@todo Дописать получение информации с учётом состояния
const std::string Player::getFullInfo() const {
    std::string res = "{";

        res += "\"level_info\" : ";
        res += "{";
            res += "\"level\" : ";
                res += std::to_string(level) + ", ";

            res += "\"exp\" : " ;
            res += "{";
                res += "\"current\" : " + std::to_string(experience) + ", ";
                res += "\"to_next_level\" : " + std::to_string(needExpToUpgrade());
            res += "}, ";

            res += "\"skill_points\" : ";
                res += std::to_string(skill_points);
        res += "}, ";

        res += "\"position\" : ";
        res += "{";
            res += "\"x\" : " + std::to_string(getCoordinates().first) + ", ";
            res += "\"y\" : " + std::to_string(getCoordinates().second);
        res += "}, ";

        res += "\"characteristics\" : ";
        res += "{";
            res += "\"hp\" : ";
            res += "{";
                res += "\"max\" : " + std::to_string(max_hp) + ", ";
                res += "\"current\" : " + std::to_string(current_hp);
            res += "}, ";

            res += "\"damage\" : ";
                res += std::to_string(damage) + ", ";

            res += std::string("\"mana\" : ");
            res += "{";
                res += "\"max\" : " + std::to_string(max_mana_count) + ", ";
                res += "\"current\" : " + std::to_string(current_mana_count);
            res += "}, ";

            res += "\"essence_count\" : ";
                res += std::to_string(essence_count);
        res += "},\n";

    res += "\"skills_info\" : ";
    res += "{";
    res += "\"skill_count\" : " + std::to_string(skills->getAllSkills().size()) + ", ";
    res += "\"skills\" : ";
    res += "[";

        size_t S = skills->getAllSkills().size(), C = 0;
        for (auto& i : skills->getAllVariations()) {
            res += "{";
            res += "\"main_name\" : " + ( "\"" + i.first + "\"") + ", ";
            res += "\"variations\" : ";
            res += "[";
            size_t s = i.second.size(), c = 0;
            for (auto &j : i.second) {
                res += "\"" + j + "\"";
                if (c < s - 1)
                    res += ", ";
                ++c;
            }
            res += "]";
            res += "}";
            if (C < S - 1)
                res += ", ";
            ++C;
        }
    res += "]";
    res += "}";
    res += "}";

    return res;
}

const std::string Player::getInfo() const {
    std::string res = "{";
    res += R"("type" : "player", )";
    res += R"("naming" : "necromancer", )";
    res += "\"level\" : " + std::to_string(level) + ", ";
    res += "\"coord\" : ";
    res += std::string("{") + "\"x\" : " + std::to_string(getCoordinates().first) + ", ";
    res += "\"y\" : " + std::to_string(getCoordinates().second) + "}, ";
    res += "\"fraction\" : " + ("\"" + convertFractionToStr(getFraction()) + "\"");
    res += "}";
    return res;
}

std::vector<std::string> Player::getAllExploredUndeadTypes() const {
    return known_undead_types;
}


