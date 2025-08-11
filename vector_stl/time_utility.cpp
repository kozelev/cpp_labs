#include "time_utility.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <iomanip>

namespace time_utility {


std::time_t CreateTime(size_t hours, size_t minutes) {

    assert(hours < 24);
    assert(minutes < 60);

    using std::chrono::system_clock;
    std::time_t current_time = system_clock::to_time_t(std::chrono::system_clock::now());
    
    std::tm* tm_result_time = localtime(&current_time);
    tm_result_time->tm_hour = hours;
    tm_result_time->tm_min = minutes;

    std::time_t result_time = mktime(tm_result_time);
    return result_time;
}


std::time_t GenerateRandomTime(std::mt19937& generator) {
    std::uniform_int_distribution<size_t> hour_randomizer(0, 23);
    std::uniform_int_distribution<size_t> minute_randomizer(0, 59);

    size_t hours = hour_randomizer(generator);
    size_t minutes = minute_randomizer(generator);

    std::time_t generated_time = CreateTime(hours, minutes);
    return generated_time;
}


bool CompareTimes(const std::time_t& first_time, const std::time_t& second_time) {
    std::tm tm1 = *localtime(&first_time);
    std::tm tm2 = *localtime(&second_time);

    return (tm1.tm_hour == tm2.tm_hour) ? (tm1.tm_min < tm2.tm_min) : (tm1.tm_hour < tm2.tm_hour);
}


void PrintTime(const std::time_t& time_to_print) {

    std::tm ltime = *localtime(&time_to_print);
    
    // time will be printed as "Tue Jul  8 07:07:38 2025"
    //std::cout << std::ctime(&time_to_print); 
    
    // time will be printed as "07:07"
    std::cout << std::put_time(&ltime, "%H:%M");
}


}  // namespace time_utility
