#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <cstdlib>
#include <iterator>
#include <type_traits>
#include <concepts>
#include <initializer_list>
#include <tuple>

template <std::default_initializable T>
class Matrix;

template <class T>
class MatrixLine {
private:
    size_t len = 0;
    T *data = nullptr;
public:
    MatrixLine() = default;
    MatrixLine(size_t size) noexcept(std::is_nothrow_default_constructible_v<T>);
    MatrixLine(const MatrixLine& o) requires std::is_copy_assignable_v<T>;
    MatrixLine(std::initializer_list<T> list) requires std::move_constructible<T>;
    MatrixLine& operator=(const MatrixLine& o) requires std::copy_constructible<T>;

    MatrixLine& operator=(MatrixLine&& o)  noexcept;

    size_t size() const;

    T& at(size_t i);
    const T& at(size_t i) const;

    ~MatrixLine();
};

template<class T>
MatrixLine<T>::MatrixLine(size_t size) noexcept(std::is_nothrow_default_constructible_v<T>) {
    len = size;
    data = new T[size];
}

template<class T>
MatrixLine<T>::MatrixLine(const MatrixLine &o) requires std::is_copy_assignable_v<T> {
    this->data = new T[o.len];
    std::copy_n(o.data, o.len, data);
    this->len = o.len;
}

template<class T>
MatrixLine<T>::MatrixLine(std::initializer_list<T> list) requires std::move_constructible<T> {
    len = list.size();
    data = new T[len];
    std::move(list.begin(), list.end(), data);
}

template<class T>
MatrixLine<T> &MatrixLine<T>::operator=(const MatrixLine &o) requires std::copy_constructible<T> {
    if (this != &o) {
        MatrixLine temp(o);
        std::swap(len, temp.len);
        std::swap(data, temp.data);
    }
    return *this;
}

template<class T>
MatrixLine<T> &MatrixLine<T>::operator=(MatrixLine &&o) noexcept {
    std::swap(len, o.len);
    std::swap(data, o.data);
    return *this;
}

template<class T>
size_t MatrixLine<T>::size() const {
    return len;
}

template<class T>
T &MatrixLine<T>::at(size_t i) {
    if (i >= len)
        throw std::out_of_range("Index must be less then len");
    return  data[i];
}

template<class T>
const T &MatrixLine<T>::at(size_t i) const {
    if (i >= len)
        throw std::out_of_range("Index must be less then len");
    return  data[i];
}

template<class T>
MatrixLine<T>::~MatrixLine() {
    delete[] data;
}

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
    typedef std::conditional_t<is_const, const T, T> *pointer_type;
    typedef std::conditional_t<is_const, const T, T> &reference_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef size_t size_type;

    MatrixIterator() : line(nullptr), index(0) {}

    template<bool other_const>
    explicit MatrixIterator(const MatrixIterator<T, other_const> &o) noexcept requires (is_const >= other_const);

    template<bool other_const>
    MatrixIterator &operator=(const MatrixIterator<T, other_const> &o) noexcept requires (is_const >= other_const);

    template<bool other_const>
    bool operator==(const MatrixIterator<T, other_const> &o) const noexcept;

    template<bool other_const>
    auto operator <=> (const MatrixIterator<T, other_const>& o) const noexcept;


    MatrixIterator& operator ++ () noexcept;
    MatrixIterator operator ++ (int) noexcept;
    MatrixIterator& operator -- () noexcept;
    MatrixIterator operator -- (int) noexcept;

    MatrixIterator& operator +=(size_type n);
    MatrixIterator operator +(difference_type n) const;
    friend MatrixIterator operator+(difference_type n, MatrixIterator It) {
        return It + n;
    }

    MatrixIterator& operator -=(size_type n);
    MatrixIterator operator -(size_type n) const;
    difference_type operator-(MatrixIterator It) const;

    reference_type operator*() const;
    pointer_type operator->() const;
    reference_type operator[](size_type n) const;

private:
    typedef std::conditional_t<is_const, const MatrixLine<T>, MatrixLine<T>>* line_ptr_t;
    line_ptr_t line;
    size_type index;

    MatrixIterator(line_ptr_t line, size_type index = 0): line(line), index(index) {}

    friend Matrix<T>;
    friend MatrixIterator<T, !is_const>;
};

template<class T, bool is_const>
template<bool other_const>
MatrixIterator<T, is_const>::MatrixIterator(const MatrixIterator<T, other_const> &o) noexcept
requires (is_const >= other_const) : line(o.line), index(o.index) {}

template<class T, bool is_const>
template<bool other_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator=(const MatrixIterator<T, other_const> &o) noexcept
        requires (is_const >= other_const) {
    line = o.line;
    index = o.index;
    return *this;
}

template<class T, bool is_const>
template<bool other_const>
bool MatrixIterator<T, is_const>::operator==(const MatrixIterator<T, other_const> &o) const noexcept {
    return (line == o.line) && (index == o.index);
}

template<class T, bool is_const>
template<bool other_const>
auto MatrixIterator<T, is_const>::operator<=>(const MatrixIterator<T, other_const> &o) const noexcept  {
    return std::tie(line, index) <=> std::tie(o.line, o.index);
}

template<class T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator++() noexcept {
    ++index;
    if (index >= line->size()) {
        index = 0;
        ++line;
    }
    return *this;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator++(int) noexcept {
    auto temp = MatrixIterator(line, index);
    ++(*this);
    return temp;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator--() noexcept {
    if (index == 0) {
        --line;
        index = line->size();
    }
    --index;
    return *this;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator--(int) noexcept {
    auto temp = MatrixIterator(line, index);
    --(*this);
    return temp;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator+=(MatrixIterator::size_type n) {
    line = line + (n + index) / line->size();
    index = (n + index) % line->size();
    return *this;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator+(MatrixIterator::difference_type n) const {
    auto temp = MatrixIterator<T, is_const>(line, index);
    temp += n;
    return temp;
}

//template<class T, bool is_const>
//MatrixIterator<T, is_const> operator+(typename MatrixIterator<T, is_const>::difference_type n, MatrixIterator<T, is_const> It) {
//    return It + n;
//}

template<class T, bool is_const>
MatrixIterator<T, is_const>& MatrixIterator<T, is_const>::operator-=(MatrixIterator<T, is_const>::size_type n) {
    line -= (n + line->size() - index) / line->size();
    index = (line->size() + index - n % line->size()) % line->size();
    return *this;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator-(MatrixIterator<T, is_const>::size_type n) const{
    auto temp = MatrixIterator(line, index);
    temp -= n;
    return temp;
}

template<class T, bool is_const>
MatrixIterator<T, is_const>::difference_type  MatrixIterator<T, is_const>::operator-(MatrixIterator It) const{
    return static_cast<difference_type>((this->line - It.line)*It.line->size() + (this->index - It.index));
}

template<class T, bool is_const>
MatrixIterator<T, is_const>::reference_type MatrixIterator<T, is_const>::operator*() const {
    return line->at(index);
}

template<class T, bool is_const>
MatrixIterator<T, is_const>::pointer_type MatrixIterator<T,is_const>::operator->() const {
    return &(line->at(index));
}

template<class T, bool is_const>
MatrixIterator<T, is_const>::reference_type MatrixIterator<T, is_const>::operator[](size_type n) const {
    return *(*this + n);
}




static_assert(std::input_iterator<MatrixIterator<int, true>>);
static_assert(std::input_iterator<MatrixIterator<int, false>>);

static_assert(std::forward_iterator<MatrixIterator<int, true>>);
static_assert(std::forward_iterator<MatrixIterator<int, false>>);

static_assert(std::bidirectional_iterator<MatrixIterator<int, true>>);
static_assert(std::bidirectional_iterator<MatrixIterator<int, false>>);

static_assert(std::random_access_iterator<MatrixIterator<int, true>>);
static_assert(std::random_access_iterator<MatrixIterator<int, false>>);




template <std::default_initializable T>
class Matrix {
public:
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference_type;

    typedef MatrixIterator<T, false> iterator;
    typedef MatrixIterator<T, true> const_iterator;
    typedef ptrdiff_t difference_type;

    typedef size_t size_type;

    Matrix() noexcept;
    Matrix(size_type m, size_type n) noexcept(std::is_nothrow_default_constructible_v<T>);
    Matrix(const Matrix& o) requires std::copy_constructible<T>;
    Matrix(Matrix&& o) noexcept;

    Matrix& operator = (const Matrix& copy)requires std::copy_constructible<T>;
    Matrix& operator = (Matrix&& moved) noexcept;

    Matrix(std::initializer_list<std::initializer_list<T>> il) requires std::move_constructible<T>;

    ~Matrix();

    iterator begin() noexcept;
    const_iterator begin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    bool operator== (const Matrix& o) const;

    void swap(Matrix& o) noexcept;

    size_type line_count() const noexcept;
    size_type line_size() const noexcept;
    size_type size() const noexcept;

    size_type max_size() const noexcept;

    bool empty() const noexcept;

    reference_type at(size_type i, size_type j);
    const_reference_type at(size_type i, size_type j) const;

private:
    size_type size_m = 0;
    MatrixLine<T>* data = nullptr;
};

template<std::default_initializable T>
Matrix<T>::Matrix() noexcept: size_m(0), data(nullptr) {}

template<std::default_initializable T>
Matrix<T>::Matrix(Matrix::size_type m, Matrix::size_type n) noexcept(std::is_nothrow_default_constructible_v<T>) {
    size_m = n;
    data = new MatrixLine<T>[n];
    for (size_type i = 0; i < n; ++i) {
        data[i] = MatrixLine<value_type>(m);
    }
}

template<std::default_initializable T>
Matrix<T>::Matrix(const Matrix &o) requires std::copy_constructible<T> {
    data = new MatrixLine<value_type>[o.size_m];
    std::copy_n(o.data, o.size_m, data);
    size_m = o.size_m;
}

template<std::default_initializable T>
Matrix<T>::Matrix(Matrix &&o) noexcept {
    swap(o);
}

template<std::default_initializable T>
Matrix<T> &Matrix<T>::operator=(const Matrix &copy) requires std::copy_constructible<T> {
    if (this != &copy) {
        Matrix temp(copy);
        swap(temp);
    }
    return *this;
}

template<std::default_initializable T>
Matrix<T> &Matrix<T>::operator=(Matrix &&moved) noexcept {
    swap(moved);
}

template<std::default_initializable T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>> il) requires std::move_constructible<T> {
    size_m = il.size();
    size_type size_n = il.begin()->size();
    for (auto &i : il) {
        if (i.size() != size_n)
            throw std::invalid_argument("Wrong size: matrix must be rectangle");
    }
    data = new MatrixLine<value_type>[size_m];
    auto curr = il.begin();
    for (size_type i = 0; i < size_m; ++i) {
        data[i] = MatrixLine<value_type>(*curr);
        ++curr;
    }
}

template<std::default_initializable T>
Matrix<T>::~Matrix() {
    delete[] data;
}

template<std::default_initializable T>
Matrix<T>::iterator Matrix<T>::begin() noexcept {
    return iterator(data, 0);
}

template<std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::begin() const noexcept {
    return const_iterator(data, 0);
}

template<std::default_initializable T>
Matrix<T>::iterator Matrix<T>::end() noexcept {
    auto *l = data + size_m;
    return iterator(l, 0);
}

template<std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::end() const noexcept {
    auto *l = data + size_m;
    return const_iterator(l, 0);
}

template<std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::cbegin() const noexcept {
    return const_iterator(data, 0);
}

template<std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::cend() const noexcept {
    auto *l = data + size_m;
    return const_iterator(l, 0);
}

template<std::default_initializable T>
bool Matrix<T>::operator==(const Matrix &o) const {
    if (this->size_m != o.size_m)
        return false;
    if (this->empty() && o.empty())
        return true;
    if (this->data[0].size() != o.data[0].size())
        return false;

    return std::equal(this->cbegin(), this->cend(), o.cbegin(),o.cend());
}

template<std::default_initializable T>
void Matrix<T>::swap(Matrix &o) noexcept {
    std::swap(data, o.data);
    std::swap(size_m, o.size_m);
}

template<std::default_initializable T>
Matrix<T>::size_type Matrix<T>::line_count() const noexcept {
    return size_m;
}

template<std::default_initializable T>
Matrix<T>::size_type Matrix<T>::line_size() const noexcept {
    return (empty())? 0 : data[0].size();
}

template<std::default_initializable T>
Matrix<T>::size_type Matrix<T>::size() const noexcept {
    return line_count() * line_size();
}

template<std::default_initializable T>
Matrix<T>::size_type Matrix<T>::max_size() const noexcept {
    return size();
}

template<std::default_initializable T>
bool Matrix<T>::empty() const noexcept {
    return size_m == 0;
}

template<std::default_initializable T>
Matrix<T>::reference_type Matrix<T>::at(Matrix::size_type i, Matrix::size_type j) {
    if (j >= size_m)
        throw std::out_of_range("Index must be less then lines count");
    return data[j].at(i);
}

template<std::default_initializable T>
Matrix<T>::const_reference_type Matrix<T>::at(Matrix::size_type i, Matrix::size_type j) const {
    if (i >= size_m)
        throw std::out_of_range("Index must be less then lines count");
    return data[j].at(i);
}
#endif //LAB3_MATRIX_H
