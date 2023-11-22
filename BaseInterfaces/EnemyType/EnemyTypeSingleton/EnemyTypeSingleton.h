#ifndef LAB3_SINGLETON_H
#define LAB3_SINGLETON_H

#include "../include/EnemyType/EnemyType.h"

template <class T>
class Singleton {
protected:
    Singleton(){};
    Singleton(const Singleton&);
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }
};

class EnemyTypeCharacteristicsCalculator {
public:
    typedef uint hp_type;
    typedef uint damage_type;

    virtual hp_type calculateMaxHP(uint level) = 0;
    virtual damage_type calculateDamage(uint level) = 0;
};

template <class T> requires std::is_same<T, EnemyType>;
class EnemyTypeSingleton : public Singleton<T>, public EnemyTypeCharacteristicsCalculator {};

#endif //LAB3_SINGLETON_H
