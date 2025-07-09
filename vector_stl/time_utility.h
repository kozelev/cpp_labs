#pragma once

#include <ctime>
#include <random>

namespace time_utility {

/**
 * Create time of current day in format \a "HH:MM".
 *
 * @param hours: amount of hours
 * @param minutes: amount of  minutes
 * @return time as std::time_t.
 */
std::time_t CreateTime(size_t hours, size_t minutes);


/**
 * Generate random time of current day in format \a "HH:MM".
 *
 * @param generator: generator which used to create random hours and minutes.
 * @return random generatred time as std::time_t.
 */
std::time_t GenerateRandomTime(std::mt19937& generator);


/**
 * Compare two times according to the following rules:
 * HH1:MM1 < HH2:MM2 if (HH1 < HH2) or ((HH1 == HH2) && (MM1 < MM2)).
 *
 * @param first_time, second_time: times to compare.
 * @return \a true if \c first_time < \c second_time, otherwise \a false.
 */
bool CompareTimes(const std::time_t& first_time, const std::time_t& second_time);


/**
 * Print time in format \a "HH:MM".
 *
 * @param time_to_print: time which needs to be printed.
 */
void PrintTime(const std::time_t& time_to_print);


}  // namespace time_utility
