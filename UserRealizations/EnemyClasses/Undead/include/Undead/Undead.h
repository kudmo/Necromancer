#ifndef LAB3_UNDEAD_H
#define LAB3_UNDEAD_H

#include <memory>

#include <ISummoner.h>

#include <Enemy/Enemy.h>
#include <UndeadType/UndeadType.h>
#include <AliveType/AliveType.h>
#include "Dungeon/Dungeon.h"

class Undead : public Enemy, public ISummoner {
public:
    Undead(Floor& f, std::pair<size_t,size_t> coord, std::unique_ptr<UndeadType>&& type, FRACTIONS fraction);
    const std::string getFullInfo() const override;
    const std::string getTypeName() const override {return "undead";}
    double getCoefficient() const;
    /*!
     * @brief Костыль для морфизма
     * @warning undead will die!!!!!!
     */
    std::unique_ptr<UndeadType> takeInnerBody();
    void die() override;
};

class UndeadBuilderFromExistingBody {
public:
    virtual Enemy& build(Floor& f, std::pair<size_t,size_t> coord, uint level, std::unique_ptr<AliveType> &&dead, FRACTIONS fraction = FRACTIONS::ENEMY) const = 0;
};

class UndeadBuilderFromNothing {
public:
    virtual Enemy& build(Dungeon& dungeon, size_t floor, std::pair<size_t,size_t> coord, uint level, FRACTIONS fraction = FRACTIONS::ENEMY) const = 0;
    virtual ~UndeadBuilderFromNothing() = default;
};

template <class T> requires std::is_base_of_v<UndeadType, T>
class UndeadBuilderAs : public UndeadBuilderFromExistingBody {
public:
    Enemy& build(Floor& f, std::pair<size_t,size_t> coord, uint level, std::unique_ptr<AliveType> &&dead, FRACTIONS fraction = FRACTIONS::ENEMY) const override {
        f.getByCoord(coord);
        auto type = std::make_unique<T>(level, std::move(dead));
        auto a = std::make_shared<Undead>(f, coord, std::move(type), fraction);
        f.summonEntity(a);
        return static_cast<Enemy&>(*a);
    }
};

template <class T, class V> requires std::is_base_of<UndeadType, T>::value && std::is_base_of<AliveType, V>::value
class UndeadBuilderBase : public UndeadBuilderFromNothing {
public:
    Enemy &build(Dungeon &dungeon, size_t floor, std::pair<size_t, size_t> coord, uint level, FRACTIONS fraction) const override {
        auto &f = dungeon.floorByNumber(floor);
        f.getByCoord(coord);
        auto alive_type = std::make_unique<V>(level);
        auto undead_type = std::make_unique<T>(level, std::move(alive_type));
        auto a = std::make_shared<Undead>(f, coord, std::move(undead_type), fraction);
        f.summonEntity(a);
        return static_cast<Enemy&>(*a);
    }
};


#endif //LAB3_UNDEAD_H
