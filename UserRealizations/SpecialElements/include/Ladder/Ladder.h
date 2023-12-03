#ifndef LAB3_LADDER_H
#define LAB3_LADDER_H

#include <cstdlib>
#include <SpecialElement/SpecialElement.h>
class Dungeon;

class Ladder : public SpecialElement{
private:
    size_t current;
    Dungeon& dungeon;
public:
    Ladder(Dungeon& d, size_t floor);

    std::string getInfo() override;

    bool isPassable() override;
    void interact(ISmartInteractor& e) override;
};

#endif //LAB3_LADDER_H
