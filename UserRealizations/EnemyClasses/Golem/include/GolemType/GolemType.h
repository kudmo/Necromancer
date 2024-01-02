#ifndef LAB3_GOLEMTYPE_H
#define LAB3_GOLEMTYPE_H

#include <cstdlib>
#include <EnemyType/EnemyType.h>
#include <memory>


class GolemType : public EnemyType {
public:
    explicit GolemType(uint level);
    virtual uint calculateIgnoringProbability(uint level) const {return 0;};
    uint getIgnoringProbability() const;
};


class GolemTypeBuilder {
public:
    virtual std::unique_ptr<EnemyType> build(uint level) = 0;
    virtual ~GolemTypeBuilder() = default;
};

template <class T> requires std::is_base_of_v<GolemType, T>
class  GolemTypeBuilderAs : public GolemTypeBuilder {
public:
    std::unique_ptr<EnemyType> build(uint level) override {
        return std::make_unique<T>(level);
    }
};
#endif //LAB3_GOLEMTYPE_H
