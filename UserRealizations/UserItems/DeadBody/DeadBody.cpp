#include "DeadBody.h"

DeadBody::DeadBody(Floor &f, std::pair<size_t, size_t> coord, AliveType *a) : who_it_was(a), Item(f, coord) {}

const AliveType &DeadBody::getType() const {
    return *who_it_was;
}

AliveType *DeadBody::takeBody()  {
    auto temp = who_it_was;
    who_it_was = nullptr;
    return temp;
}