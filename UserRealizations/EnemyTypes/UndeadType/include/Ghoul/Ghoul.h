#ifndef LAB3_GHOUL_H
#define LAB3_GHOUL_H

#include <UndeadType/UndeadType.h>
#include <AliveType/AliveType.h>


class Ghoul : public UndeadType {
public:
    Ghoul(uint level, std::unique_ptr<AliveType>&& who);
    double calculateCoefficient(uint level) const override;
    const std::string getNaming() const override;
};



#endif //LAB3_GHOUL_H
