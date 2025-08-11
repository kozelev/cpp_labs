#include "tests.h"

#include <type_traits>


int main() {

    static_assert(!std::is_same_v<std::forward_list<int32_t>, List>,
                  "You cannot use std::forward_list, cheater!");
    static_assert(!std::is_base_of_v<std::forward_list<int32_t>, List>,
                  "You cannot use std::forward_list, cheater!");
    static_assert(!std::is_same_v<std::list<int32_t>, List>, "You cannot use std::list, cheater!");
    static_assert(!std::is_base_of_v<std::list<int32_t>, List>, "You cannot use std::list, cheater!");

    default_constructible_tests();
    std::cout << "default_constructible_tests -> ok" << std::endl;

    simple_push_pop_tests();
    std::cout << "simple_push_pop_tests -> ok" << std::endl;

    copying_tests();
    std::cout << "copying_tests -> ok" << std::endl;

    clear_tests();
    std::cout << "clear_tests -> ok" << std::endl;

    iterator_tests();
    std::cout << "iterator_tests -> ok" << std::endl;

    remove_tests();
    std::cout << "remove_tests -> ok" << std::endl;

    output_tests();
    std::cout << "output_tests -> ok" << std::endl;

    std::cout << "Success!!!! :)" << std::endl;

    return 0;
}
