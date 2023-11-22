#include <iostream>

class SpecialElement {
public:
    virtual bool isPassable() = 0;
    virtual ~SpecialElement() = default;
};

class Wall : public SpecialElement {
public:
    Wall() = default;
    bool isPassable() override;
    ~Wall() = default;
};

bool Wall::isPassable() {return false;}

class Ladder : public SpecialElement{
private:
    size_t from;
    size_t to;
public:
    Ladder(size_t from, size_t to) : from(from), to(to) {}
    bool isPassable() override;
    ~Ladder() = default;
};

bool Ladder::isPassable() {return true;}

class Door : public SpecialElement {
private:
    bool opened = false;
public:
    Door() = default;
    bool isPassable() override;
    ~Door() = default;
};

bool Door::isPassable() {return opened;}

class I {
public:
    virtual void a() = 0;
    virtual ~I() = default;
};
class A : public I {
public:
    A() = default;
    void a() override;
    ~A() = default;
};

void A::a()  {std::cout << "A" << std::endl;}

class B : public I {
public:
    B() = default;
    void a() override;
    ~B() = default;
};

void B::a() {std::cout << "B" << std::endl;}

int main() {
    SpecialElement *a = static_cast<SpecialElement*>(new Wall());
    SpecialElement *b = static_cast<SpecialElement*>(new Door());
    std::cout << a->isPassable() << std::endl;
    std::cout << b->isPassable() << std::endl;

    delete a;
    delete b;
//    I* a = new A();
//    I* b = new B();
//    a->a();
//    b->a();
//    delete a;
//    delete b;
    return  0;
}