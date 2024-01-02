#ifndef LAB3_ALIVETYPE_H
#define LAB3_ALIVETYPE_H

#include <cstdlib>
#include <memory>

#include <EnemyType/EnemyType.h>

class AliveType : public EnemyType {
public:
    explicit AliveType(uint level);
};

class AliveTypeBuilder {
public:
    virtual std::unique_ptr<AliveType> build(uint level) = 0;
    virtual ~AliveTypeBuilder() = default;
};

template <class T> requires std::is_base_of_v<AliveType, T>
class  AliveTypeBuilderAs : public AliveTypeBuilder {
public:
    std::unique_ptr<AliveType> build(uint level) override {
        return std::make_unique<T>(level);
    }
};
#endif //LAB3_ALIVETYPE_H
