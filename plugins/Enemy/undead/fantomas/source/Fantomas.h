#ifndef LAB3_GHOUL_H
#define LAB3_GHOUL_H

#include "UndeadType/UndeadType.h"
#include "AliveType/AliveType.h"


class Fantomas : public UndeadType {
public:
    Fantomas(uint level, std::unique_ptr<AliveType>&& who);
    double calculateCoefficient(uint level) const override;
    const std::string getNaming() const override;
};



#endif //LAB3_GHOUL_H
