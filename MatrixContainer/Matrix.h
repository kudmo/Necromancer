#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <cstdlib>
#include <iterator>
#include <type_traits>
#include <iostream>

template <class T> requires std::is_default_constructible_v<T>
class Matrix;

template <class T>
class MatrixLine {
private:
    size_t len = 0;
    T *data = nullptr;
public:
    MatrixLine() = default;
    MatrixLine(size_t size) noexcept(std::is_nothrow_default_constructible_v<T>) {
        len = size;
        data = new T[size];
    }
    MatrixLine(MatrixLine& o) requires std::copy_constructible<T> {
        this->data = new T[o.len];
        for (size_t i = 0; i < o.len; ++i) {
            data[i] = o.data[i];
        }
        this->len = o.len;
    }
    MatrixLine(std::initializer_list<T> list) requires std::move_constructible<T> {
        this->len = list.size();
        this->data(list);
    }
    MatrixLine& operator=(MatrixLine& o) requires std::copy_constructible<T> {
        if (this != &o) {
            MatrixLine temp(o);
            std::swap(len, temp.len);
            std::swap(data, temp.data);
        }
        return *this;
    }

    MatrixLine& operator=(MatrixLine&& o) requires std::copy_constructible<T> {
        std::swap(len, o.len);
        std::swap(data, o.data);
        return *this;
    }
    ~MatrixLine() {
        delete[] data;
    }

    size_t size() const {return len;}

    T* at(size_t i) {
        if (i >= len)
            throw std::out_of_range("Index must be less then len");
        return  data + i;
    }
};

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

    MatrixIterator() : line(nullptr), index(0) {}

    template<bool other_const>
    MatrixIterator(const MatrixIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) : line(o.line), index(o.index) {}

    ~MatrixIterator() = default;
    template<bool other_const>
    MatrixIterator& operator = (const MatrixIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) {
            line = o.line;
            index = o.index;
            return *this;
        }

    template<bool other_const>
    bool operator == (const MatrixIterator<T, other_const>& o) const noexcept {
        return (line == o.line) && (index == o.index);
    }

    template<bool other_const>
    bool operator != (const MatrixIterator<T, other_const>& o) const noexcept {
        return !(*this == o);
    }

    template<bool other_const>
    bool operator < (const MatrixIterator<T, other_const>& o) const noexcept {
        if (this->line < o.line)
            return true;
        else if (this->line == o.line)
            return this->index < o.index;
        return false;
    }

    template<bool other_const>
    bool operator > (const MatrixIterator<T, other_const>& o) const noexcept {
        if (this->line > o.line)
            return true;
        else if (this->line == o.line)
            return this->index > o.index;
        return false;
    }

    template<bool other_const>
    bool operator <= (const MatrixIterator<T, other_const>& o) const noexcept {
        return !(*this > o);
    }

    template<bool other_const>
    bool operator >= (const MatrixIterator<T, other_const>& o) const noexcept {
        return !(*this < o);
    }

    //!@todo а вот в какой момент остановиться - вопрос, потому что в такой вариации он уйдёт за границу двумерного массива)
    MatrixIterator& operator ++ () noexcept {
        ++index;
        if (index >= line->size()) {
            index = 0;
            ++line;
        }
        return *this;
    }
    MatrixIterator operator ++ (int) noexcept {
        auto temp = MatrixIterator(line, index);
        ++(*this);
        return temp;
    }
    MatrixIterator& operator -- () noexcept {
        if (index == 0) {
            --line;
            index = line->size();
        }
        --index;
        return *this;
    }
    MatrixIterator operator -- (int) noexcept {
        auto temp = MatrixIterator(line, index);
        --(*this);
        return temp;
    }

    MatrixIterator& operator +=(size_type n) const {
        line += (n + index) / line->size();
        index = (n + index) % line->size();
        return *this;
    }
    MatrixIterator operator +(size_type n) const {
        auto temp = MatrixIterator(line, index);
        temp.ptr_value += n;
        return temp;
    }
    friend MatrixIterator operator+(size_type n, MatrixIterator It) {
        return It + n;
    }

    MatrixIterator& operator -=(size_type n) const {
        line -= (n + line->size() - index) / line->size();
        index = (line->size() + index - n % line->size()) % line->size();
        return *this;
    }
    MatrixIterator operator -(size_type n) const {
        auto temp = MatrixIterator(line, index);
        temp.ptr_value -= n;
        return temp;
    }
    difference_type operator-(MatrixIterator It) const {
        return static_cast<difference_type>((this->line - It.line) + (this->index - It.index));
    }

    reference_type operator*() const {
        if (!line)
            throw std::runtime_error("empty iterator");
        return *(line->at(index));
    }
    pointer_type operator->() const {
        return line->at(index);
    }
    reference_type operator[](size_type n) const {
        return *(*this + n);
    }

private:
    typedef std::conditional_t<is_const, const MatrixLine<T>, MatrixLine<T>>* line_ptr_t;
    line_ptr_t line;
    size_type index;

    MatrixIterator(line_ptr_t line, size_type index = 0): line(line), index(index) {}

    friend Matrix<T>;
    friend MatrixIterator<T, !is_const>;
};

static_assert(std::input_iterator<MatrixIterator<int, true>>);
static_assert(std::input_iterator<MatrixIterator<int, false>>);

static_assert(std::forward_iterator<MatrixIterator<int, true>>);
static_assert(std::forward_iterator<MatrixIterator<int, false>>);

static_assert(std::bidirectional_iterator<MatrixIterator<int, true>>);
static_assert(std::bidirectional_iterator<MatrixIterator<int, false>>);

static_assert(std::random_access_iterator<MatrixIterator<int, true>>);
static_assert(std::random_access_iterator<MatrixIterator<int, false>>);



template <class T>  requires std::is_default_constructible_v<T>
class Matrix {
public:
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference_type;

    typedef MatrixIterator<T, false> iterator;
    typedef MatrixIterator<T, true> const_iterator;
    typedef ptrdiff_t difference_type;

    typedef size_t size_type;

    // Конструкторы
        // обязательные для контейнера
    Matrix() noexcept(std::is_nothrow_default_constructible_v<T>): size_m(0), data(nullptr) {}
    Matrix(size_type m, size_type n) {
        size_m = m;
        data = new MatrixLine<T>[n];
        for (size_type i = 0; i < n; ++i) {
            data[i] = MatrixLine<value_type>(m);
        }
    }
    Matrix(const Matrix& o) requires std::copy_constructible<T> {
        data = new MatrixLine<value_type>[o.size_m];
        for (size_t i = 0; i < o.size_m; ++i) {
            data[i] = o.data[i];
        }
        size_m = o.size_m;
    }
    Matrix(Matrix&& o) noexcept(std::is_nothrow_default_constructible_v<T>) {
        std::swap(size_m, o.size_m);
        std::swap(data, o.data);
    }

    Matrix& operator = (const Matrix& copy)requires std::copy_constructible<T> {
        if (this != &copy) {
            Matrix temp(copy);
            std::swap(size_m, temp.size_m);
            std::swap(data, temp.data);
        }
        return *this;
    }
    Matrix& operator = (Matrix&& moved) noexcept {
        std::swap(size_m, moved.size_m);
        std::swap(data, moved.data);
    }


    Matrix(std::initializer_list<std::initializer_list<T>> il) requires std::move_constructible<T> {
        size_m = il.size();
        size_type size_n = il.begin()->size();
        for (auto &i : il) {
            if (i.size() != size_n)
                throw std::invalid_argument("Wrong size: matrix must be rectangle");
        }
        data = new MatrixLine<value_type>[size_m];
        auto curr = il.begin();
        for (size_type i = 0; i < size_m; ++i) {
            data[i] = MatrixLine<value_type>(curr);
            ++curr;
        }
    }

    ~Matrix() {
        delete[] data;
    }

    // Операции
        // обязательные для контейнера
    iterator begin() noexcept {
        return iterator(data, 0);
    }
    iterator end() noexcept {
        if (data) {
            auto *l = data + (size_m - 1);
            return iterator (l, l->size() - 1);
        }
        return iterator(nullptr, 0);
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(data, 0);
    }
    const_iterator cend() const noexcept {
        if (data) {
            auto *l = data + (size_m - 1);
            return const_iterator (l, l->size() - 1);
        }
        return const_iterator(nullptr, 0);
    }

        // а зачем, если есть cbegin и cend?
//    const_iterator begin() const noexcept;
//    const_iterator end() const noexcept;


    bool operator== (const Matrix& o) const {
        if (this->size_m != o.size_m)
            return false;
        if ((this->data) ^ (o.data))
            return false;
        if (this->empty() && o.empty())
            return true;
        if (this->data[0].size() != o.data[0].size())
            return false;

        const_iterator i = cbegin();
        const_iterator j = o.cbegin();
        while (i != cend()) {
            if (i != j)
                return false;
            ++i;
            ++j;
        }
        return true;
    }
    bool operator!= (const Matrix& o) const {
        return !(*this == o);
    }

    void swap(Matrix& o) noexcept {
        std::swap(size_m, o.size_m);
        std::swap(data, o.data);
    }

    size_type line_count() const noexcept {
        return size_m;
    }
    size_type line_size() const noexcept {
        return (empty())? 0 : data[0].size();
    }
    size_type size() const noexcept {
        return line_count() * line_size();
    }

    size_type max_size() const noexcept {
        return size();
    }

    bool empty() const noexcept {
        return size_m == 0;
    }

    reference_type at(size_type i, size_type j) {
        if (i >= size_m)
            throw std::out_of_range("I must be less then lines count");
        return *data[j].at(i);
    }
private:
    size_type size_m = 0;
    MatrixLine<T>* data;
};
#endif //LAB3_MATRIX_H
