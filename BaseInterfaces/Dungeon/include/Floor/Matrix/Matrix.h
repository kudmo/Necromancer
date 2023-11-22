#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <cstdlib>
#include <utility>

template <class T>
class Matrix {
    typedef T value_t;
    typedef T* pointer_t;
    typedef T& reference_t;
public:
    Matrix(size_t, size_t);
    reference_t at(size_t, size_t);
};

#endif //LAB3_MATRIX_H