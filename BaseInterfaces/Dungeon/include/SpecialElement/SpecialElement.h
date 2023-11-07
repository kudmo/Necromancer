#ifndef LAB3_SPECIALELEMENT_H
#define LAB3_SPECIALELEMENT_H

class SpecialElement {
public:
    virtual bool isPassable() = 0;
    virtual void interact(ISmartInteractor&) = 0;
};

class ISmartInteractor {

};
#endif //LAB3_SPECIALELEMENT_H
