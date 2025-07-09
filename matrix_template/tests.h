// tests.h

#ifndef TESTS_H

#define TESTS_H

#include "matrix.h"

#include <cassert>
#include <sstream>
#include <vector>


namespace Utils {

template<size_t M, size_t N, typename Field>
void CheckMatrix(const Matrix<M, N, Field>& actual,
                 const std::vector<std::vector<Field>>& expected) {
    assert(M == expected.size());
    assert(N == expected[0].size());
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            //if (actual(i, j) != expected[i][j]) {
            //    std::cout << "i: " << i << "j: " << j << std::endl;
            //    std::cout << "Actual:\n";
            //    std::cout << actual << std::endl;
            //    std::cout << "Expected:\n";
            //    std::cout << Matrix<M, N, Field>(expected);
            //}
            assert(actual(i, j) == expected[i][j]);
        }
    }
}

template<size_t N, typename Field>
void CheckIdentityMatrix(const Matrix<N, N, Field>& matrix) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i == j) {
                // if (matrix(i, j) != Field(1)) {
                //     std::cout << "i: " << i << "j: " << j << std::endl;
                //     std::cout << "Actual:\n";
                //     std::cout << matrix << std::endl;
                // }
                assert(matrix(i, j) == Field(1));
            } else {
                assert(matrix(i, j) == Field(0));
            }
        }
    }
}

template<typename T>
void CheckVectors(const std::vector<T>& actual, const std::vector<T>& expected) {
    assert(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        assert(actual[i] == expected[i]);
    }
}

} // namespace Utils


namespace MatrixTests {

void default_constructible_tests() {

    static_assert(std::is_default_constructible_v<Matrix<3, 3, int>>,
                  "No default constructor for square matrices!");
    static_assert(!std::is_default_constructible_v<Matrix<3, 4, int>>,
                  "Matrix has default constructor for non-square matrices!");

    static_assert(std::is_default_constructible_v<Matrix<3, 3>>,
                  "No default constructor for square matrices!");
    static_assert(!std::is_default_constructible_v<Matrix<3, 4>>,
                  "Matrix has default constructor for non-square matrices!");
    
    static_assert(std::is_default_constructible_v<SquareMatrix<3, int>>,
                  "No default constructor for square matrices!");

    static_assert(std::is_default_constructible_v<SquareMatrix<3>>,
                  "No default constructor for square matrices!");

    {
        Matrix<2, 2, int> matrix;
        Utils::CheckIdentityMatrix(matrix);
    }

    {
        SquareMatrix<10, int64_t> matrix;
        Utils::CheckIdentityMatrix(matrix);
    }
}

void vector_constructible_tests() {
    {
        std::vector<std::vector<int>> v_matrix = {{1,2},{4,5},{7,8}};
        Matrix<3, 2, int> matrix(v_matrix);
        Utils::CheckMatrix(matrix, v_matrix);
    }
    {
        std::vector<std::vector<double>> v_matrix = {{1.0,2.0,3.4},{4.7,5.0,6.2}};
        Matrix<2, 3, double> matrix(v_matrix);
        Utils::CheckMatrix(matrix, v_matrix);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1,2,3},{4,5,6},{7,8,9}};
        SquareMatrix<3, int> matrix(v_matrix);
        Utils::CheckMatrix(matrix, v_matrix);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int64_t> matrix(v_matrix);
        Utils::CheckMatrix(matrix,
            std::vector<std::vector<int64_t>>{{1,2,3}, {4,5,6}});
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1,2,3}, {4,5,6}};
        Matrix<2, 3> matrix(v_matrix);
        Utils::CheckMatrix(matrix,
            std::vector<std::vector<Rational>>{{1,2,3}, {4,5,6}});
    }
}

void comparison_tests() {
    {
        std::vector<std::vector<int>> v_matrix = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int> a(v_matrix);
        Matrix<2, 3, int> b(v_matrix);
        assert(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int64_t> a(v_matrix);
        Matrix<2, 3, int> b(v_matrix);
        assert(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int> a(v_matrix);
        Matrix<2, 2, int> b;
        assert(a != b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1,2,3}, {4,5,6}}; 
        std::vector<std::vector<int>> v_matrix_b = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3, int> b(v_matrix_b);
        assert(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1,2,3}, {4,5,6}}; 
        std::vector<std::vector<int>> v_matrix_b = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3, int64_t> b(v_matrix_b);
        assert(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1,2,3}, {4,5,6}}; 
        std::vector<std::vector<int>> v_matrix_b = {{1,2,3}, {4,5,6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3> b(v_matrix_b);
        assert(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1,2,3}, {4,5,6}}; 
        std::vector<std::vector<int>> v_matrix_b = {{1,2,3}, {5,5,6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3> b(v_matrix_b);
        assert(a != b);
    }

}

void arithmetic_tests() {
    std::vector<std::vector<int>> v_matrix = {{1,2,3}, {4,5,6}}; 
    Matrix<2, 3, int> a(v_matrix);
    Matrix<2, 3, int> b(v_matrix);

    // +, -, +=, -=
    Utils::CheckMatrix(a + a, std::vector<std::vector<int>>{{2,4,6}, {8,10,12}}); 
    Utils::CheckMatrix(a - a, std::vector<std::vector<int>>{{0,0,0}, {0,0,0}});

    Utils::CheckMatrix(Matrix<3, 3>() + Matrix<3, 3>(), 
        std::vector<std::vector<Rational>>{{2,0,0}, {0,2,0}, {0,0,2}});
    
    Utils::CheckMatrix(SquareMatrix<3>() + SquareMatrix<3>(), 
        std::vector<std::vector<Rational>>{{2,0,0}, {0,2,0}, {0,0,2}});

    Utils::CheckMatrix(Matrix<3, 3, double>() - Matrix<3, 3, double>(), 
        std::vector<std::vector<double>>{{0,0,0}, {0,0,0}, {0,0,0}});

    Utils::CheckMatrix(SquareMatrix<3, int>() - SquareMatrix<3, int>(), 
        std::vector<std::vector<int>>{{0,0,0}, {0,0,0}, {0,0,0}});

    a += b;
    Utils::CheckMatrix(a, std::vector<std::vector<int>>{{2,4,6}, {8,10,12}});
    a += a;
    Utils::CheckMatrix(a, std::vector<std::vector<int>>{{4,8,12}, {16,20,24}}); 
    a -= b;
    Utils::CheckMatrix(a, std::vector<std::vector<int>>{{3,6,9}, {12,15,18}});
    a -= a;
    Utils::CheckMatrix(a,  std::vector<std::vector<int>>{{0,0,0}, {0,0,0}}); 
    a += b;
    Utils::CheckMatrix(a,  std::vector<std::vector<int>>{{1,2,3}, {4,5,6}});

    // *(Field), *=(Field)
    Utils::CheckMatrix(a * 1, v_matrix);
    Utils::CheckMatrix(a * 2, std::vector<std::vector<int>>{{2,4,6}, {8,10,12}});
    Utils::CheckMatrix(a * 3, std::vector<std::vector<int>>{{3,6,9}, {12,15,18}});
    a *= 1;
    Utils::CheckMatrix(a,  std::vector<std::vector<int>>{{1,2,3}, {4,5,6}}); 
    a *= 5;
    Utils::CheckMatrix(a,  std::vector<std::vector<int>>{{5,10,15}, {20,25,30}});

    // *, *= 
    Utils::CheckIdentityMatrix(SquareMatrix<3>() * SquareMatrix<3>());
    Utils::CheckIdentityMatrix(SquareMatrix<5>() * SquareMatrix<5>());
    Utils::CheckIdentityMatrix(SquareMatrix<10>() * SquareMatrix<10>());
    Utils::CheckIdentityMatrix(SquareMatrix<100>() * SquareMatrix<100>());
    //Utils::CheckIdentityMatrix(SquareMatrix<500>() * SquareMatrix<500>());
    
    Matrix<3, 2, int> c(std::vector<std::vector<int>>{{1,4}, {2,5}, {3,6}});
    static_assert(std::is_same_v<decltype(b * c), Matrix<2, 2, int>>,
        "Matrix operator* returns matrix with wrong dimensions!!!");
    Utils::CheckMatrix(b * c, std::vector<std::vector<int>>{{14,32}, {32,77}});

    static_assert(std::is_same_v<decltype(c * b), Matrix<3, 3, int>>,
        "Matrix operator* returns matrix with wrong dimensions!!!");
    Utils::CheckMatrix(c * b, 
        std::vector<std::vector<int>>{{17,22,27}, {22,29,36}, {27,36,45}});
    
    std::vector<std::vector<Rational>> d_matrix = {{1,2,3}, {4,5,6}, {7,8,9}};
    Matrix<3, 3> d(d_matrix);
    d *= SquareMatrix<3>{};
    Utils::CheckMatrix(d, d_matrix);
    d *= d;
    Utils::CheckMatrix(d,
        std::vector<std::vector<Rational>>{{30,36,42}, {66,81,96}, {102,126,150}});
    d *= SquareMatrix<3>{};
    Utils::CheckMatrix(d,
        std::vector<std::vector<Rational>>{{30,36,42}, {66,81,96}, {102,126,150}});

}

void determinant_tests() {

    {
        Matrix<10, 10, int> m;
        assert(m.det() == 1); // 1
    }
    
    {
        Matrix<2, 2, int> m(std::vector<std::vector<int>>{{1, 2}, {3,4}});
        assert(m.det() == -2); // -2
    }
    
    {
        Matrix<2, 2, int> m(std::vector<std::vector<int>>{{21, 1}, {3, 4}});
        assert(m.det() == 81); // 81
    }

    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, 
                                                          {0, 0, 0},
                                                          {5, 4, 3}});
        assert(m.det() == 0); // 0
    }
    
    {
        Matrix<3, 3> m(std::vector<std::vector<Rational>>{{1, -3, 4}, 
                                                          {2, 5, -3},
                                                          {4, -2, 7}});
        assert(m.det() == Rational(11)); // 11
    }

    {
        Matrix<4, 4, int> m(std::vector<std::vector<int>>{{1, 2, 3, 4}, 
                                                          {5, 7, 3, 5},
                                                          {6, 8, 7, 6},
                                                          {11, -2, 6, 9}});
        assert(m.det() == -861); // -861
    }

    {
        Matrix<100, 100, int> m;
        assert(m.det() == 1); // 1
    }
    
    //{
    //    Matrix<500, 500, int> m;
    //    assert(m.det() == 1); // 1
    //}  
}

void transposed_tests() { 
    Matrix<2, 3, int> a(
        std::vector<std::vector<int>>{{1,2,3}, {4,5,6}});
    static_assert(std::is_same_v<decltype(a.transposed()), Matrix<3, 2, int>>,
        "Method transposed() returns matrix with wrongs dimensions!!!");
    Utils::CheckMatrix(a.transposed(),
        std::vector<std::vector<int>>{{1,4}, {2,5}, {3,6}});
    
    SquareMatrix<100> e;
    Utils::CheckIdentityMatrix(e.transposed());
}

void rank_tests() {
    {
        Matrix<2, 3, int> m(std::vector<std::vector<int>>{{1,2,4}, {4,5,6}});
        assert(m.rank() == 2u);
    }
    {
        Matrix<3, 2, int> m(std::vector<std::vector<int>>{{1,2}, {2,4}, {3,6}});
        assert(m.rank() == 1u);
    }
    {
        Matrix<3, 2> m(std::vector<std::vector<int>>{{2,3}, {4,6}, {6,7}});
        assert(m.rank() == 2u);
    }
    {
        Matrix<3, 2, int> m(std::vector<std::vector<int>>{{1,2}, {2,3}, {4,5}});
        assert(m.rank() == 2u);
    }
    {
        Matrix<3, 3, int> m(
            std::vector<std::vector<int>>{{1,2,3}, {2,4,6}, {3,6,9}});
        assert(m.rank() == 1u);
    }
    {
        Matrix<3, 3, int> m(
            std::vector<std::vector<int>>{{1,2,3}, {4,5,6}, {7,8,9}});
        assert(m.rank() == 2u);
    }
    {
        const Matrix<3, 3> m(
            std::vector<std::vector<int>>{{1,2,3}, {4,5,6}, {7,8,7}});
        assert(m.rank() == 3u);
    }
    {
        SquareMatrix<100> m;
        assert(m.rank() == 100u);
    }
    {
        const SquareMatrix<100> m;
        assert(m.rank() == 100u);
    }
    {
        Matrix<3, 4, int> m3(
            std::vector<std::vector<int>>{{1,2,3,4}, {1,2,7,9}, {1,2,7,8}});
        assert(m3.rank() == 3u);
    }
    {
        Matrix<3, 4, int> m3(
            std::vector<std::vector<int>>{{1,2,3,4}, {1,2,7,9}, {1,2,7,9}});
        assert(m3.rank() == 2u);
    }
    {
        Matrix<3, 4, int> m3(
            std::vector<std::vector<int>>{{1,2,3,4}, {1,2,3,4}, {1,2,3,4}});
        assert(m3.rank() == 1u);
    }
}

void trace_tests() {
    {
        Matrix<3, 3, int> m(
            std::vector<std::vector<int>>{{1,2,3}, {2,4,6}, {3,6,9}});
        assert(m.trace() == 14);
    }
    {
        Matrix<3, 3, int> m(
            std::vector<std::vector<int>>{{1,2,3}, {4,5,6}, {7,8,9}});
        assert(m.trace() == 15);
    }
    {
        const Matrix<3, 3> m(
            std::vector<std::vector<int>>{{0,2,3}, {14,5,6}, {27,8,7}});
        assert(m.trace() == Rational(12));
    }
    {
        SquareMatrix<100> m;
        assert(m.trace() == Rational(100));
    }
    {
        const SquareMatrix<100> m;
        assert(m.trace() == Rational(100));
    }
}

void invert_tests() {
    {
        SquareMatrix<3> m;
        Utils::CheckIdentityMatrix(m.inverted());
        m.invert();
        Utils::CheckIdentityMatrix(m);
    }
    {
        SquareMatrix<10> m;
        Utils::CheckIdentityMatrix(m.inverted());
        m.invert();
        Utils::CheckIdentityMatrix(m);
    }
    {
        SquareMatrix<50> m;
        Utils::CheckIdentityMatrix(m.inverted());
        m.invert();
        Utils::CheckIdentityMatrix(m);
    }
    {
        Matrix<3, 3> m(std::vector<std::vector<int>>{{1,2,3}, {4,5,6}, {7,8,7}});
        Utils::CheckIdentityMatrix(m * m.inverted());
        Utils::CheckMatrix(m.inverted(), 
            std::vector<std::vector<Rational>>{{ {-13,6}, {5, 3}, {-1, 2} },
                                               { {7, 3}, {-7, 3}, {1, 1} },
                                               { {-1, 2}, {1, 1}, {-1, 2} }});
        m.invert();
        Utils::CheckMatrix(m, 
            std::vector<std::vector<Rational>>{{ {-13,6}, {5, 3}, {-1, 2} },
                                               { {7, 3}, {-7, 3}, {1, 1} },
                                               { {-1, 2}, {1, 1}, {-1, 2} }});
    }
    {
        Matrix<3, 3, int> m(
            std::vector<std::vector<int>>{{2,1,1}, {3,2,1}, {2,1,2}});
        Utils::CheckIdentityMatrix(m * m.inverted());
        Utils::CheckMatrix(m.inverted(),
            std::vector<std::vector<int>>{{3,-1,-1}, {-4,2,1}, {-1,0,1}});
        m.invert();
        Utils::CheckMatrix(m,
            std::vector<std::vector<int>>{{3,-1,-1}, {-4,2,1}, {-1,0,1}});
    }
}

void getting_row_column_tests() {
    {
        SquareMatrix<3> m;
        static_assert(std::is_same_v<decltype(m.getRow(1)), std::vector<Rational>>,
            "Method getRow(size_t) must return std::vector<Field>!!!");
        static_assert(std::is_same_v<decltype(m.getColumn(1)), std::vector<Rational>>,
            "Method getColumn(size_t) must return std::vector<Field>!!!");
        for (size_t i = 0; i < 3; ++i) {
            assert(m.getRow(i) == m.getColumn(i));
        }
    }
    {
        Matrix<3, 4, int> m(std::vector<std::vector<int>>{{1,2,3,4}, 
                                                          {5,6,7,8},
                                                          {1,0,1,0}});
        Utils::CheckVectors(m.getRow(0), std::vector<int>{1,2,3,4});
        Utils::CheckVectors(m.getRow(1), std::vector<int>{5,6,7,8});
        Utils::CheckVectors(m.getRow(2), std::vector<int>{1,0,1,0});
        Utils::CheckVectors(m.getColumn(0), std::vector<int>{1,5,1});
        Utils::CheckVectors(m.getColumn(1), std::vector<int>{2,6,0});
        Utils::CheckVectors(m.getColumn(2), std::vector<int>{3,7,1});
        Utils::CheckVectors(m.getColumn(3), std::vector<int>{4,8,0});
    }
    {
        const Matrix<4, 3, int> m(std::vector<std::vector<int>>{{1,2,3}, 
                                                                {5,6,7},
                                                                {1,0,1},
                                                                {2,5,4}});
        Utils::CheckVectors(m.getRow(0), std::vector<int>{1,2,3});
        Utils::CheckVectors(m.getRow(1), std::vector<int>{5,6,7});
        Utils::CheckVectors(m.getRow(2), std::vector<int>{1,0,1});
        Utils::CheckVectors(m.getRow(3), std::vector<int>{2,5,4});
        Utils::CheckVectors(m.getColumn(0), std::vector<int>{1,5,1,2});
        Utils::CheckVectors(m.getColumn(1), std::vector<int>{2,6,0,5});
        Utils::CheckVectors(m.getColumn(2), std::vector<int>{3,7,1,4});
    }
}

void indexes_tests() {
    const Matrix<3, 4, int> m(std::vector<std::vector<int>>{{1,2,3,4}, 
                                                            {5,6,7,8},
                                                            {1,0,1,0}});
    assert(m[0][0] == 1 && m(0, 0) == 1);
    assert(m[1][2] == 7 && m(1, 2) == 7);
    assert(m[2][3] == 0 && m(2, 3) == 0);
    
    SquareMatrix<3> m1(std::vector<std::vector<Rational>>{{1,2,0},
                                                          {0,1,3},
                                                          {1,1,1}});
    assert(m1[0][0] == 1 && m1(0, 0) == 1);
    m1[0][1] = 0;
    m1(1, 2) = 0;
    m1[2][0] = 0;
    m1(2, 1) = 0;
    Utils::CheckIdentityMatrix(m1);
}

void input_output_tests() {
    {
        Matrix<3, 4, int> m(std::vector<std::vector<int>>(3, std::vector<int>(4)));
        std::stringstream ss("1 2 3 4 5 6 7 8 9 10 11 12");
        ss >> m;
        Utils::CheckMatrix(m,
            std::vector<std::vector<int>>{{1,2,3,4}, {5,6,7,8}, {9,10,11,12}});
    }
    {
        SquareMatrix<3, int> m(std::vector<std::vector<int>>{{1,2,3},
                                                             {4,5,6},
                                                             {7,8,9}});
        std::stringstream ss;
        ss << m;
        SquareMatrix<3, int> m1;
        ss >> m1;
        Utils::CheckMatrix(m1,
            std::vector<std::vector<int>>{{1,2,3},{4,5,6},{7,8,9}});
    }
}

} // namespace MatrixTests


#endif // TESTS_H

