#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <cstdlib>

template <T>
class Matrix{
public:
    Matrix(size_t x, size_t y);
    T* at(size_t x, size_t y);
};
#endif //LAB3_MATRIX_H
