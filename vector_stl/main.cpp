#include "time_utility.h"
#include "train.h"

#include <iostream>

int main() {

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = CreateTime(0, 30);
    std::time_t t2 = GenerateRandomTime(generator);

    PrintTime(t1);
    std::cout << '\n';
    PrintTime(t2);
    std::cout << '\n';
    std::cout << "t1 < t2: " << std::boolalpha << CompareTimes(t1, t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << CompareTimes(t2, t1) << '\n';



    return EXIT_SUCCESS;
}
