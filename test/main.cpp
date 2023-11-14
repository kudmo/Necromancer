#include <iostream>

class A {
public:
    int a;
};
class B {
private:
    const A& a;
public:
    B(const A& a): a(a) {;}
    int get() const {return a.a;}
};

int main() {
    A a;
    a.a = 12;
    B b1(a), b2(a), b3(a);
    std::cout << b1.get() << std::endl;
    std::cout << b2.get() << std::endl;
    std::cout << b3.get() << std::endl;
    a.a = 21;
    std::cout << b1.get() << std::endl;
    std::cout << b2.get() << std::endl;
    std::cout << b3.get() << std::endl;
    return  0;
}