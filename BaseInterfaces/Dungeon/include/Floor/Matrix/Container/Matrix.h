#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <cstdlib>
#include <iterator>
#include <type_traits>


/*!
 * @brief Класс итератора для матрицы
 * @tparam T  адресуемый итератором тип
 * @tparam is_const итератор является const_iterator если true,
 *                  обычным iterator в ином случае
 */
template<class T, bool is_const>
class MatrixIterator {
public:

    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef std::conditional_t<is_const, const T, T>* pointer_type;
    typedef std::conditional_t<is_const, const T, T>& reference_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef size_t size_type;
    MatrixIterator();

    template<bool other_const>
    MatrixIterator(const MatrixIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) : value(o.value) {}

    ~MatrixIterator();

    template<bool other_const>
    MatrixIterator& operator = (const MatrixIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) {
            value = o.value;
            return *this;
        }

    template<bool other_const>
    bool operator == (const MatrixIterator<T, other_const>& o) const noexcept;

    template<bool other_const>
    bool operator != (const MatrixIterator<T, other_const>& o) const noexcept;

    template<bool other_const>
    bool operator < (const MatrixIterator<T, other_const>& o) const noexcept;

    template<bool other_const>
    bool operator > (const MatrixIterator<T, other_const>& o) const noexcept;

    template<bool other_const>
    bool operator <= (const MatrixIterator<T, other_const>& o) const noexcept;

    template<bool other_const>
    bool operator >= (const MatrixIterator<T, other_const>& o) const noexcept;


    MatrixIterator& operator ++ () noexcept;
    MatrixIterator operator ++ (int) noexcept;
    MatrixIterator& operator -- () noexcept;
    MatrixIterator operator -- (int) noexcept;

    MatrixIterator& operator +=(size_type) const;
    MatrixIterator operator +(size_type) const;

    MatrixIterator& operator -=(size_type) const;
    MatrixIterator operator -(size_type) const;

    reference_type operator*() const;
    pointer_type operator->() const;
    reference_type operator[](size_type) const; //optional

private:
    pointer value;

    MatrixIterator(pointer value): value(value) {}

    friend Matrix<T>;
    friend MatrixIterator<T, !is_const>;
};

static_assert(std::random_access_iterator<MatrixIterator<int>, false>);
static_assert(std::random_access_iterator<MatrixIterator<int, true>);

template <class T>
class Matrix{

private:
    size_t size_n = 0;
    size_t size_m = 0;


public:
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference_type;

    typedef MatrixIterator<T, false> iterator;
    typedef MatrixIterator<T, true> const_iterator;
    typedef ptrdiff_t difference_type;

    typedef size_t size_type;

    // noexcept если T() это noexcept
    Matrix() noexcept(std::is_nothrow_default_constructible_v<T>);
    // Работает только если есть T() и T(a)
    Matrix(const Matrix& o) requires std::copy_constructible<T>;
    Matrix(Matrix&& o)noexcept(std::is_nothrow_default_constructible_v<T>);

    Matrix(size_type n, const T& t) requires std::copy_constructible<T>;

    template<std::input_iterator It>
    Matrix(It i, It j) requires std::constructible_from<T , std::iter_reference_t<It>>;

    Matrix(std::initializer_list<T> il) requires std::move_constructible<T>;

    // Работает только если есть T() и T(a)
    Matrix& operator = (const Matrix& o)requires std::copy_constructible<T>;

    Matrix& operator = (Matrix&& o) noexcept;

    ~Matrix();
};
#endif //LAB3_MATRIX_H
