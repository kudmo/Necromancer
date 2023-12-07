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
    explicit MatrixLine(size_t size) noexcept(std::is_nothrow_default_constructible_v<T>);
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
 * @brief Iterator-class for matrix
 * @tparam T the type addressed by the iterator
 * @tparam is_const iterator is const_iterator if true,
 *                  common iterator else
 */
template<class T, bool is_const>
class MatrixIterator {
public:
//! @brief A type indicating the distance between two iterators
    typedef ptrdiff_t difference_type;
//! @brief The type addressed by the iterator
    typedef T value_type;
/*!
* @brief Type of pointer to a stored value,
* for const_iterator - const T*, for regular - T*
*/
    typedef std::conditional_t<is_const, const T, T> *pointer_type;
/*!
 * @brief The type of reference to the stored value,
 * for const_iterator - const T&, for regular - T&
 */
    typedef std::conditional_t<is_const, const T, T> &reference_type;
/*!
 * @brief Iterator category
 */
    typedef std::random_access_iterator_tag iterator_category;

/*!
 * @brief is an empty constructor, dereferencing the created iterator will result in UB
 * @note Implements default_initializable from regular
 */
    MatrixIterator() : line(nullptr), index(0) {}

/*!
 * @brief Copying Constructor
 * @tparam other_const The constancy of the copied iterator
 * @note Allows copying an iterator of a different constancy
 * @note Implements std::move_constructible and std::copy_constructible
 */
    template<bool other_const>
    explicit MatrixIterator(const MatrixIterator<T, other_const> &o) noexcept requires (is_const >= other_const);

/*!
 * @brief Copying assignment
 * @returns Link to the passed iterator
 * @tparam other_const The constancy of the iterator being copied
 * @note Allows copying an iterator of a different constancy
 * @note Implements std::assignable_from<T&,T>, std::copyable and std::swappable
 */
    template<bool other_const>
    MatrixIterator &operator=(const MatrixIterator<T, other_const> &o) noexcept requires (is_const >= other_const);

/*!
 * @brief Comparison of iterators (equality)
 * @tparam other_const The constancy of the iterator being copied
 * @returns true if iterators refer to the same element,
 * otherwise false
 * @note Operator != we get it automatically
 */
    template<bool other_const>
    bool operator==(const MatrixIterator<T, other_const> &o) const noexcept;

/*!
 * @brief Comparison of iterators (ordering)
 * @tparam other_const The constancy of the iterator being copied
 * @returns true if iterators refer to the same element,
 * otherwise false
 * @note Operators <, <=, >, >= we get it automatically
 */
    template<bool other_const>
    auto operator <=> (const MatrixIterator<T, other_const>& o) const noexcept;


/*!
 * @brief Moves the iterator to the next matrix cell
 * @returns Link to the passed iterator
 * @note Implements `{ ++i } -> std::same_as<I&>` from weakly_incrementable
 */
    MatrixIterator& operator ++ () noexcept;
/*!
* @brief Moves the iterator to the next matrix cell
* @returns The state of the iterator before modification
* @note Implements `{i++ } -> std::same_as<I>` from incrementable
*/
    MatrixIterator operator ++ (int) noexcept;
/*!
* @brief Moves the iterator to the previous matrix cell
* @returns Link to the passed iterator
* @note Implements `{ --i } -> std::same_as<I&>` from bidirectional_iterator
*/
    MatrixIterator& operator -- () noexcept;
/*!
* @brief Moves the iterator to the previous matrix cell
* @returns The state of the iterator before modification
* @note Implements `{i-- } -> std::same_as<I>` from bidirectional_iterator
*/
    MatrixIterator operator -- (int) noexcept;
/*!
* @brief Moves the iterator forward by n elements
* @param n The number of elements by which the iterator is shifted
* @returns Link to the passed iterator
*/
    MatrixIterator& operator +=(difference_type n);
/*!
* @brief Create the iterator forward by n elements
* @param n The number of elements by which the iterator is shifted
* @returns  Created iterator
*/
    MatrixIterator operator +(difference_type n) const;
/*!
* @brief Create the iterator forward by n elements
* @param n The number of elements by which the iterator is shifted
* @returns  Created iterator
*/
    friend MatrixIterator operator+(difference_type n, MatrixIterator It) {
        return It + n;
    }
/*!
 * @brief Moves the iterator backward by n elements
 * @param n The number of elements by which the iterator is shifted
 * @returns Link to the passed iterator
 */
    MatrixIterator& operator -=(difference_type n);
/*!
 * @brief Create the iterator backward by n elements
 * @param n The number of elements by which the iterator is shifted
 * @returns  Created iterator
 */
    MatrixIterator operator -(difference_type n) const;
    /*!
     * @brief Calculates the difference between the two iterators
     * @param It The iterator with which the difference is located
     * @return The difference between the two iterators
     */
    difference_type operator-(MatrixIterator It) const;
/*!
 * @brief Dereference
 * @returns Link to the addressable matrix cell
 * @note Implements `{ *i } -> / *can-reference* /` from input_or_output_iterator and indirectly_readable
 */
    reference_type operator*() const;
/*!
 * @brief Accessing element fields
 * @returns A pointer to the addressable matrix cell
 */
    pointer_type operator->() const;
/*!
 * @brief Access to the matrix cell, n from the current iterator
 * @param n The difference between the current iterator and the desired iterator
 * @returns Pointer to the addressable cell of the matrix
 */
    reference_type operator[](difference_type n) const;

private:
    //! @brief Type of pointer to the matrix line
    typedef std::conditional_t<is_const, const MatrixLine<T>, MatrixLine<T>>* line_ptr_t;
    //! @brief The matrix line that the iterator points to
    line_ptr_t line;
    //! @brief The number of the cell in the line that the iterator points to
    size_t index;

    //! @brief Constructor in the private area, for use in Matrix
    explicit MatrixIterator(line_ptr_t line, size_t index = 0): line(line), index(index) {}

    //! @note Matrix can access private fields
    friend Matrix<T>;
    //! @note Iterator of opposite constancy can access private fields
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
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator+=(MatrixIterator::difference_type n) {
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
MatrixIterator<T, is_const>& MatrixIterator<T, is_const>::operator-=(MatrixIterator<T, is_const>::difference_type n) {
    line -= (n + line->size() - index) / line->size();
    index = (line->size() + index - n % line->size()) % line->size();
    return *this;
}

template<class T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator-(MatrixIterator<T, is_const>::difference_type n) const{
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
MatrixIterator<T, is_const>::reference_type MatrixIterator<T, is_const>::operator[](MatrixIterator<T, is_const>::difference_type n) const {
    return *(*this + n);
}


// Matrix can access private fields

static_assert(std::input_iterator<MatrixIterator<int, true>>);
static_assert(std::input_iterator<MatrixIterator<int, false>>);

static_assert(std::forward_iterator<MatrixIterator<int, true>>);
static_assert(std::forward_iterator<MatrixIterator<int, false>>);

static_assert(std::bidirectional_iterator<MatrixIterator<int, true>>);
static_assert(std::bidirectional_iterator<MatrixIterator<int, false>>);

static_assert(std::random_access_iterator<MatrixIterator<int, true>>);
static_assert(std::random_access_iterator<MatrixIterator<int, false>>);



/*!
 * @brief Matrix (rectangle)
 * @tparam T Type of stored values
 */
template <std::default_initializable T>
class Matrix {
public:
    //! @brief Type of stored values
    typedef T value_type;
    //! @brief Reference to the type of stored values
    typedef T& reference_type;
    //! @brief Const reference to the type of stored values
    typedef const T& const_reference_type;

    //! @brief Type of iterator
    typedef MatrixIterator<T, false> iterator;
    //! @brief Type of const iterator
    typedef MatrixIterator<T, true> const_iterator;
    //! @brief A type indicating the distance between two iterators,
    typedef ptrdiff_t difference_type;
    //! @brief The type used to represent the size of the container
    typedef size_t size_type;

    /*!
     * @brief Empty constructor, creates an empty matrix
     */
    Matrix() noexcept;
    /*!
     * @brief A constructor that creates an empty matrix M x N
     * @param m Number of columns
     * @param n Number of rows
     * @note noexect if T() is noexept
     */
    Matrix(size_type m, size_type n) noexcept(std::is_nothrow_default_constructible_v<T>);
    /*!
     * @brief The copying constructor
     * @param other The matrix being copied
     * @note It only works if there are T() and T(a)
     */
    Matrix(const Matrix& other) requires std::copy_constructible<T>;
    /*!
     * @brief Moving Constructor
     * @param other The matrix that is being moved
     * @note It only works if there are T(T&& moved)
     */
    Matrix(Matrix&& other) noexcept requires std::move_constructible<T>;
    /*!
     * @brief The matrix constructor from the initializing list
     * @param il initializing list of matrix data (list of rows(list of cells))
     * @throws std::invalid_argument If the rows of the matrix are of different lengths
     */
    Matrix(std::initializer_list<std::initializer_list<T>> il) requires std::move_constructible<T>;

    /*!
     * @brief Copying assignment operator
     * @param copy The matrix being copied
     * @note This only works if there is a copying assignment at T
     */
    Matrix& operator = (const Matrix& copy) requires std::is_copy_assignable_v<T>;
/*!
 * @brief Moving assignment operator
 * @param copy The matrix being moved
 * @note This only works if there is a moving assignment at T
 */
    Matrix& operator = (Matrix&& moved) noexcept requires std::is_move_assignable_v<T>;

/*!
 * @brief Destructor
 */
    ~Matrix();

/*!
 * @brief Getting the iterator to the begin of the matrix
 * @returns Iterator addressing the beginning of the matrix
 */
    iterator begin() noexcept;
/*!
 * @brief Getting the const iterator to the begin of the matrix
 * @returns Const iterator addressing the beginning of the matrix
 */
    const_iterator begin() const noexcept;
/*!
 * @brief Getting the iterator to the end of the matrix
 * @returns Iterator addressing the ending of the matrix
 */
    iterator end() noexcept;
/*!
 * @brief Getting the const iterator to the end of the matrix
 * @returns Const iterator addressing the ending of the matrix
 */
    const_iterator end() const noexcept;
/*!
 * @brief Getting the const iterator to the begin of the matrix
 * @returns Const iterator addressing the beginning of the matrix
 */
    const_iterator cbegin() const noexcept;
/*!
 * @brief Getting the const iterator to the end of the matrix
 * @returns Const iterator addressing the ending of the matrix
 */
    const_iterator cend() const noexcept;
/*!
 * @brief Comparing two matrices
 * @returns true if equal, otherwise false
 * @note Also generates !=
 */
    bool operator== (const Matrix& o) const;

/*!
 * @brief Exchanges the states of two matrices with each other
 * @param other Matrix for state exchange
 */
    void swap(Matrix& other) noexcept;

/*!
 * @brief Returns the number of rows in the matrix
 * @returns The number of rows in the matrix
 */
    size_type line_count() const noexcept;
/*!
 * @brief Returns the size of rows in the matrix
 * @returns The size of rows in the matrix
 */
    size_type line_size() const noexcept;
/*!
 * @brief Returns the size of the container
 * @returns Container size
 */
    size_type size() const noexcept;
/*!
 * @brief Returns the maximum possible container size
 * @returns The maximum possible container size
 */
    size_type max_size() const noexcept;
/*!
 * @brief Checking the matrix for emptiness
 * @returns true if the matrix is empty, otherwise false
 */
    bool empty() const noexcept;

/*!
 * @brief Returns a reference to the i element of the j row
 * @param i Number of element in row (starts from 0)
 * @param j Number of row (starts from 0)
 * @return Reference to the i element of the j row
 * @throws std::out_of_range If j (row number) more then rows count
 * @throws std::out_of_range If i (number of element in row) more then row size
 */
    reference_type at(size_type i, size_type j);
/*!
 * @brief Returns a const reference to the i element of the j row
 * @param i Number of element in row (starts from 0)
 * @param j Number of row (starts from 0)
 * @return Const reference to the i element of the j row
 * @throws std::out_of_range If j (row number) more then rows count
 * @throws std::out_of_range If i (number of element in row) more then row size
 */
    const_reference_type at(size_type i, size_type j) const;

private:
    //! @brief Number of rows
    size_type size_m = 0;
    //! @brief Array of rows
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
Matrix<T>::Matrix(Matrix &&o) noexcept requires std::move_constructible<T> {
    swap(o);
}

template<std::default_initializable T>
Matrix<T> &Matrix<T>::operator=(const Matrix &copy) requires std::is_copy_assignable_v<T>{
    if (this != &copy) {
        Matrix temp(copy);
        swap(temp);
    }
    return *this;
}

template<std::default_initializable T>
Matrix<T> &Matrix<T>::operator=(Matrix &&moved) noexcept requires std::is_move_assignable_v<T> {
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
