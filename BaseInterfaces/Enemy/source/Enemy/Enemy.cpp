#include <Enemy/Enemy.h>
#include <SubSkill/SubSkill.h>
#include <EnemyType/EnemyType.h>
#include <IExperienceCollector.h>
#include <thread>
#include <cmath>

Enemy::Enemy(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<EnemyType>  &&type, FRACTIONS fraction) :
        Entity(f, coord, fraction)
{
    this->type = std::move(type);

    if (!this->type)
        throw enemy_errors::invalid_type_error("type must be not nullptr");

    this->current_hp = this->type->getMaxHp();
    this->skill = nullptr;
}

Enemy::Enemy(Floor &f, std::pair<size_t, size_t> coord, std::unique_ptr<EnemyType> &&type, FRACTIONS fraction, std::unique_ptr<SubSkill>&& skill)
        : Entity(f, coord, fraction)
{
    this->type = std::move(type);
    if (!this->type)
        throw enemy_errors::invalid_type_error("type must be not nullptr");

    this->current_hp = type->getMaxHp();
    this->skill = std::move(skill);
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
    return *target_of_hunting.lock();
}

void Enemy::damaged(IAttacker &attacker, uint damage)  {
    std::scoped_lock lock(m_is_target);
    if (isDead())
        return;

    auto r_damage = std::min(damage, current_hp);
    current_hp -= r_damage;
    if (current_hp == 0) {
        auto *temp = dynamic_cast<IExperienceCollector*>(&attacker);
        if (temp)
            temp->collectExperience(getExperienceCount());
        die();
    }
}

void Enemy::useSkill(Object &target) {
    if (!skill)
        throw enemy_errors::invalid_skill_error("No skill to use");
    skill->skill(getLevel(), *this, target);
}



struct Node {
    std::pair<size_t,size_t> coord;
    size_t len;
    Node *prev;
    DIRECTIONS dir_prev;
};
struct PathNode {
    std::pair<size_t,size_t> coord;
    DIRECTIONS dir_next;
    PathNode *next = nullptr;
};

bool operator < (Node& l, Node& r) {return  l.len < r.len;}
size_t calculate_distance (std::pair<size_t,size_t>& l, std::pair<size_t,size_t>& r) {
    size_t X, Y;
    if (l.first > r.first)
        X = l.first - r.first;
    else
        X = r.first - l.first;

    if (l.second > r.second)
        Y = l.second - r.second;
    else
        Y = r.second - l.second;

    return X + Y;
}
double calculate_real_distance (std::pair<size_t,size_t>& l, std::pair<size_t,size_t>& r) {
    double X, Y;
    if (l.first > r.first)
        X = static_cast<double >(l.first - r.first);
    else
        X = static_cast<double >(r.first - l.first);

    if (l.second > r.second)
        Y = static_cast<double >(l.second - r.second);
    else
        Y = static_cast<double >(r.second - l.second);

    return std::sqrt(X*X + Y*Y);
}
std::vector<Node*>::iterator chooseNode(std::vector<Node*>& reachable, std::pair<size_t,size_t> to) {
    size_t min = -1;
    std::vector<Node*>::iterator best;
    for (auto i = reachable.begin(); i < reachable.end(); ++i) {
        if ((*i)->coord == to) return i;
        auto start_len = (*i)->len;
        auto len_node_to_goal = calculate_distance((*i)->coord, to);
        auto total_len = start_len + len_node_to_goal;
        if (min == total_len && calculate_real_distance((*best)->coord, to) > calculate_real_distance((*i)->coord, to)) {
            best = i;
        } else if (min > total_len) {
            min = total_len;
            best = i;
        }
    }
    return best;
}

std::vector<Node*> get_adjacent_nodes(Floor& f, Node *node) {
    std::vector<Node*> res;
    try {
        auto t1 = f.getNextByDirection(node->coord, DIRECTIONS::UP);
        if (f.getByCoord(t1).isPassable()) {
            res.push_back(new Node({t1, node->len + 1, node, DIRECTIONS::UP}));
        }
    } catch (dungeon_errors::invalid_position_error&) {}
    try {
        auto t2 = f.getNextByDirection(node->coord, DIRECTIONS::RIGHT);
        if (f.getByCoord(t2).isPassable()) {
            res.push_back(new Node({t2, node->len + 1, node, DIRECTIONS::RIGHT}));
        }
    } catch (dungeon_errors::invalid_position_error&) {}
    try {
        auto t3 = f.getNextByDirection(node->coord, DIRECTIONS::DOWN);
        if (f.getByCoord(t3).isPassable()) {
            res.push_back(new Node({t3, node->len + 1, node, DIRECTIONS::DOWN}));
        }
    } catch (dungeon_errors::invalid_position_error&) {}
    try {
        auto t4 = f.getNextByDirection(node->coord, DIRECTIONS::LEFT);
        if (f.getByCoord(t4).isPassable()) {
            res.push_back(new Node({t4, node->len + 1, node, DIRECTIONS::LEFT}));
        }
    } catch (dungeon_errors::invalid_position_error&) {}
    return res;
}


PathNode *build_path(std::vector<Node*> &r, std::vector<Node*> &e, Node *goal) {
    auto *goal_p = new PathNode();
    goal_p->coord = goal->coord;
    goal_p->next = nullptr;

    for (auto &i : r) {
        Node *curr = goal;
        bool flag = true;
        while (curr != nullptr) {
            if (i == curr) {
                flag = false;
                break;
            }
            curr = curr->prev;
        }
        if (flag)
            delete i;
    }
    for (auto &i : e) {
        Node *curr = goal;
        bool flag = true;
        while (curr != nullptr) {
            if (i == curr) {
                flag = false;
                break;
            }
            curr = curr->prev;
        }
        if (flag)
            delete i;
    }

    Node *curr = goal->prev;
    Node *curr_n = goal;

    PathNode *next = goal_p;
    while (curr) {
        PathNode *c = new PathNode();
        c->coord = curr->coord;
        c->dir_next = curr_n->dir_prev;
        c->next = next;
        next = c;

        curr_n = curr;
        curr = curr->prev;
    }
    while (goal) {
        Node *t = goal->prev;
        delete goal;
        goal = t;
    }

    if (next->next) {
        if (next->coord.first == next->next->coord.first) {
            if (next->coord.second < next->next->coord.second)
                next->dir_next = DIRECTIONS::DOWN;
            else
                next->dir_next = DIRECTIONS::UP;
        } else {
            if (next->coord.first < next->next->coord.first)
                next->dir_next = DIRECTIONS::RIGHT;
            else
                next->dir_next = DIRECTIONS::LEFT;
        }
    }
    return next;
}

PathNode* findWay(Floor& f, std::pair<size_t,size_t> from, std::pair<size_t,size_t> to) {
    std::vector<Node*> reachable;
    reachable.push_back(new Node({from, 0, nullptr}));
    std::vector<Node*> explored;

    while (!reachable.empty()) {
        // Don't repeat ourselves.
        auto node = chooseNode(reachable, to);

        // If we just got to the goal node, build and return the path.
        if ((*node)->coord == to) {
            PathNode *path = build_path(reachable, explored, *node);
            return path;
        }

        // Don't repeat ourselves.
        auto node_ = *node;
        explored.push_back(node_);
        reachable.erase(node);

        // Where can we get from here that we haven't explored before?
        auto new_reachable_ = get_adjacent_nodes(f, node_);
        std::vector<Node*> new_reachable;

        for (auto i = new_reachable_.begin(); i < new_reachable_.end();++i) {
            bool flag = true;
            for (auto &j : explored) {
                if ((*i)->coord == j->coord) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                new_reachable.push_back(*i);
            else
                delete *i;
        }

        for (auto &i : new_reachable) {
            bool flag = true;
            Node *c = i;
            for (auto &j : reachable) {
                if (i->coord == j->coord) {
                    flag = false;
                    c = j;
                    break;
                }
            }
            if (flag) {
                reachable.push_back(i);
            } else {
                delete i;
            }
            if (node_->len + 1 <= c->len) {
//                c->prev = node_;
                c->len = node_->len + 1;
            }
        }
    }

    for (auto &i : reachable)
        delete i;
    for (auto &i : explored)
        delete i;
    return nullptr;
}
void clearWay(PathNode* path) {
    while (path) {
        PathNode *temp = path->next;
        delete path;
        path = temp;
    }
}
void Enemy::scanTerritory() {
    //!@todo переделать на нормальное разбиение на КС и поиск противника в КС
    std::weak_ptr<Entity> find_target;
    for (auto &entity : getFloor().getEntities()) {
        std::shared_ptr<Entity> e = entity.lock();
        if (this->getFraction() != e->getFraction()) {
            PathNode *path = findWay(getFloor(), getCoordinates(), e->getCoordinates());
            if (path) {
                find_target = std::weak_ptr<Entity>(e);
                clearWay(path);
                break;
            }
            clearWay(path);
        }
    }
    target_of_hunting = find_target;
}

void Enemy::hunt() {
    if (!target_of_hunting.expired()) {
        auto target_p = target_of_hunting.lock();
        if (target_p->getCoordinates() == this->getCoordinates()) {
            attack(*target_p);
        } else {
            PathNode *path = findWay(getFloor(), getCoordinates(), target_p->getCoordinates());
/*
        PathNode *nec = path;
        if (nec) {
            std::cout << "Path to" <<std::endl;
            while (nec) {
                std::cout << "\t" << nec->coord.first << " " << nec->coord.second << " - "
                          << static_cast<int>(nec->dir_next) << std::endl;
                nec = nec->next;
            }
        } else {
            std::cout << "No way" <<std::endl;
        }
*/

            if (path && path->next) {
                if (path->next->coord == target_p->getCoordinates())
                    attack(*target_p);
                else {
                    this->rotate(path->dir_next);
                    this->move();
                }
            } else {
                target_of_hunting.reset();
            }

            clearWay(path);
        }
    } else {
        scanTerritory();
    }
}

const std::string Enemy::getInfo() const {
    std::string res = "{";
    res += "\"type\" : \"" + getTypeName() + "\", ";
    res += "\"naming\" : \"" + getNaming() + "\", ";
    res += "\"level\" : " + std::to_string(getLevel()) + ", ";
    res += "\"coord\" : ";
    res += std::string("{") + "\"x\" : " + std::to_string(getCoordinates().first) + ", ";
    res += "\"y\" : " + std::to_string(getCoordinates().second) + "}, ";
    res += "\"fraction\" : " + ("\"" + convertFractionToStr(getFraction()) + "\"");
    res += "}";
    return res;
}







