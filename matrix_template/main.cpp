#include "tests.h"

#include <iostream>

int main() {
    
    using namespace MatrixTests;

    std::cout << "default_constructible_tests: ";
    default_constructible_tests();
    std::cout << "ok\n";

    std::cout << "vector_constructible_tests: ";
    vector_constructible_tests();
    std::cout << "ok\n";

    std::cout << "comparison_tests: ";
    comparison_tests();
    std::cout << "ok\n";

    std::cout << "arithmetic_tests: ";
    arithmetic_tests();
    std::cout << "ok\n";

    std::cout << "determinant_tests: ";
    determinant_tests();
    std::cout << "ok\n";

    std::cout << "transposed_tests: ";
    transposed_tests();
    std::cout << "ok\n";

    std::cout << "rank_tests: ";
    rank_tests();
    std::cout << "ok\n";

    std::cout << "trace_tests: ";
    trace_tests();
    std::cout << "ok\n";

    std::cout << "invert_tests: ";
    invert_tests();
    std::cout << "ok\n";

    std::cout << "getting_row_column_tests: ";
    getting_row_column_tests();
    std::cout << "ok\n";

    std::cout << "indexes_tests: ";
    indexes_tests();
    std::cout << "ok\n";

    std::cout << "input_output_tests: ";
    input_output_tests();    
    std::cout << "ok\n";
    

    return 0;
}
