#include <catch2/catch.hpp>
#include <Matrix.h>
#include <initializer_list>
#include <cstdlib>
//#include "../../MatrixContainer/Matrix.h"

TEST_CASE("MatrixConstructors") {
    SECTION("Default") {
        Matrix<int> m;
        REQUIRE(m.size() == 0);
        REQUIRE(m.empty());
        REQUIRE(m.begin() == m.end());
        REQUIRE(m.max_size() == m.size());
    }
    SECTION("With size") {
        auto m = Matrix<int>(3,5);
        REQUIRE(m.size() == 3*5);
        REQUIRE(m.empty() == false);
        REQUIRE(m.line_size() == 3);
        REQUIRE(m.line_count() == 5);
        REQUIRE(m.max_size() == m.size());
    }
    SECTION("Copy") {
        Matrix<int> m = Matrix<int>(4,2);
        for (auto i = m.begin(); i < m.end(); ++i) {
            *i = 1;
        }
        Matrix<int> m_copy = Matrix<int>(m);
        REQUIRE(m.size() == m_copy.size());
        REQUIRE(m.line_count() == m_copy.line_count());
        REQUIRE(m.line_size() == m_copy.line_size());
        REQUIRE(std::equal(m.cbegin(), m.cend(), m_copy.cbegin(),m_copy.cend()));
        REQUIRE(m == m_copy);
        m_copy.at(1,1) = 12;
        REQUIRE(m_copy.at(1,1) != m.at(1,1));
        REQUIRE(m != m_copy);

    }
    SECTION("Move") {
        Matrix<int> m = Matrix<int>(4,2);
        for (auto i = m.begin(); i < m.end(); ++i) {
            *i = 1;
        }
        Matrix<int> m_copy = Matrix<int>(m);
        Matrix<int> m_move = Matrix<int>(std::move(m));
        REQUIRE(m_move.size() == m_copy.size());
        REQUIRE(m_move.line_count() == m_copy.line_count());
        REQUIRE(m_move.line_size() == m_copy.line_size());
        REQUIRE(std::equal(m_copy.cbegin(), m_copy.cend(), m_move.cbegin(),m_move.cend()));
    }
    SECTION("InitializerList") {
        SECTION("Correct") {
            Matrix<int> m = Matrix<int>({{1, 2, 3},
                                         {4, 5, 6}});
            REQUIRE(m.size() == 2 * 3);
            REQUIRE(m.empty() == false);
            REQUIRE(m.line_size() == 3);
            REQUIRE(m.line_count() == 2);
            REQUIRE(m.at(0, 0) == 1);
            REQUIRE(m.at(1, 0) == 2);
            REQUIRE(m.at(2, 0) == 3);
            REQUIRE(m.at(0, 1) == 4);
            REQUIRE(m.at(1, 1) == 5);
            REQUIRE(m.at(2, 1) == 6);
        }
        SECTION("Incorrect") {
            REQUIRE_THROWS_AS(Matrix<int>({{1, 2, 3},{4, 5}}), std::invalid_argument);
        }
    }
}

TEST_CASE("MatrixMethods") {
    SECTION("Equality") {
        SECTION("DifferentSizes") {
            auto m1 = Matrix<int>(3,5);
            auto m2 = Matrix<int>(2,5);
            REQUIRE(m1 != m2);

            auto m3 = Matrix<int>(3,5);
            auto m4 = Matrix<int>(3,6);
            REQUIRE(m4 != m3);

            Matrix<int> m5;
            Matrix<int> m6;
            REQUIRE(m5 != m3);
            REQUIRE(m5 == m6);

            auto m7 = Matrix<int>(2,3);
            auto m8 = Matrix<int>(3,2);
            REQUIRE(m7 != m8);
        }

        SECTION("ByValues") {
            auto m1 = Matrix<int>({{1,2,3}});
            auto m2 = Matrix<int>({{1,2,3}});
            REQUIRE(m1 == m2);
            m1.at(1,0) = 3;
            REQUIRE(m1 != m2);

            auto m3 = Matrix<int>({{1,1},{2,2},{3,3},{4,4}});
            auto m4 = Matrix<int>({{1,1},{2,2},{0,3},{4,4}});
            REQUIRE(m3 != m4);
            m4.at(0,2) = 3;
            REQUIRE(m3 == m4);

            const Matrix<int> m5 = Matrix<int>({{1,1},{2,2},{3,3},{4,4}});
            REQUIRE(m3 == m5);
        }
    }
}
TEST_CASE("MatrixIterators") {
    SECTION("Arithmetic") {
        SECTION("Increment-Decrement") {
            auto m = Matrix<int>(10,5);
            MatrixIterator<int, false>::difference_type diff;
            diff = GENERATE(take(2, random(static_cast<size_t>(10), static_cast<size_t>(25))));
            auto It1 = m.begin();
            It1 = It1 + diff;
            auto It2 = It1;
            REQUIRE(++It1 > It2);
            REQUIRE(--It1 == It2);
            REQUIRE(--It1 < It2);
            REQUIRE(++It1 == It2);

            REQUIRE(It1++ == It2);
            REQUIRE(It1 != It2);
            REQUIRE(It1 > It2);
            --It1;
            REQUIRE(It1-- == It2);
            REQUIRE(It1 < It2);
        }
        SECTION("Incrementing-Decrementig between lines") {
            Matrix<int> m = Matrix<int>({{1, 2, 3},
                                         {4, 5, 6}});
            auto It1 = m.begin() + 3;
            REQUIRE((*It1) == 4);
            REQUIRE(*(--It1) == 3);
            REQUIRE(*(++It1) == 4);
        }
        SECTION("Plus-Minus") {
            auto m = Matrix<int>(10,5);
            MatrixIterator<int, false>::difference_type diff;
            diff = GENERATE(take(2, random(static_cast<size_t>(10), static_cast<size_t>(25))));
            auto It1 = m.begin();
            It1 = It1 + diff;
            auto It2 = It1 + diff;
            REQUIRE(It2 - diff == It1);
            REQUIRE(It1 + diff == diff + It1);
            REQUIRE(m.end() - m.begin() == m.size());
        }
        SECTION("Operators []") {
            Matrix<int> m = Matrix<int>({{1, 2, 3},
                                         {4, 5, 6}});
            auto It1 = m.begin();
            auto It2 = m.begin();
            for (size_t i = 0; i < m.size(); ++i, ++It2)
                REQUIRE(It1[i] == *It2);
        }
    }
}