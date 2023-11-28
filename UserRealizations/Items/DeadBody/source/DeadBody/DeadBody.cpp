#include <DeadBody/DeadBody.h>
#include <AliveType/AliveType.h>

DeadBody::DeadBody(Floor &f, std::pair<size_t, size_t> coord, AliveType *a) : Item(f, coord), who_it_was(a) {}

const AliveType &DeadBody::getType() const {
    return *who_it_was;
}

AliveType *DeadBody::takeBody()  {
    auto temp = who_it_was;
    who_it_was = nullptr;
    return temp;
}

DeadBody::~DeadBody() {
    delete who_it_was;
}
