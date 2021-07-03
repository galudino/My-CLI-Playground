/*!
    \file       main.cpp
    \brief      Client source file to test countdown/countup with timestamp

    \author     Gemuele Aludino
    \date       02 Jul 2021
 */

#include "timestamp.hpp"

#include <iostream>
#include <chrono>
#include <thread>

/*!
    \tparam NumberType  integral or floating point type, or any type with operator+, operator-, and operator%
    
    \param[in]  min     The minimum value, inclusive
    \param[in]  max     The maximum value, exclusive
 
    \return     A random value from [min, max)
 */
template <typename NumberType>
NumberType random_closed_range(NumberType min, NumberType max) {
    return (std::rand() % (max - min)) + min;
}

/*!
    \tparam NumberType  integral or floating point type, or any type with operator+, operator-, and operator%
    
    \param[in]  min     The minimum value, inclusive
    \param[in]  max     The maximum value, exclusive
 
    \return     A random value from [min, max]
 */
template <typename NumberType>
NumberType random_range(NumberType min, NumberType max) {
    std::srand(std::time(nullptr));
    return (std::rand() % ((max + 1) - min)) + min;
}

/*!
    \returns    A random boolean, false or true
 */
bool random_bool() {
    std::srand(std::time(nullptr));
    return (std::rand() % (true + 1) - false) + false;
}

void timestamp_demo();
void random_demo();

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    random_demo();
}

void timestamp_demo() {
    // Start at 00:00:05
    auto time = timestamp(0, 0, 5);
    
    // End at 00:00:00.
    // time will become 00:00:00 after count_down_to
    auto end = timestamp::midnight;
    
    // End at 00:00:00 after time does count_up_to.
    auto start = timestamp(0, 0, 5);
    
    using std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<high_resolution_clock>;
    
    auto start_timer = time_point();
    auto stop_timer = time_point();
    
    start_timer = high_resolution_clock::now();

    std::cout << "[counting down] ";
    time.count_down_to(end, std::cout);
    std::cout << '\n';
    
    stop_timer = high_resolution_clock::now();
    
    const auto duration_down = duration_cast<std::chrono::milliseconds>(stop_timer - start_timer);
    std::cout << "Timer ran for: " << duration_down.count() << "ms" << std::endl;
    
    start_timer = high_resolution_clock::now();
    
    std::cout << "[counting up]   ";
    time.count_up_to(start, std::cout);
    std::cout << '\n';
    
    stop_timer = high_resolution_clock::now();
    const auto duration_up = duration_cast<std::chrono::milliseconds>(stop_timer - start_timer);
    std::cout << "Timer ran for: " << duration_up.count() << "ms" << std::endl;
}

void random_demo() {
    constexpr auto min = 10000;
    constexpr auto max = 60000;
    
    using std::chrono_literals::operator""ms;
    using std::string_literals::operator""s;
    
    auto label = "random number generation: [10000, 60000): "s;
    std::cout << label;
    
    auto move_back_chars = std::string(5, '\b');
    move_back_chars += std::string(5, ' ');
    move_back_chars += std::string(5, '\b');
    
    for (auto i = 0; i < 100; i++) {
        std::cout << random_closed_range(min, max);
        std::cout.flush();
        std::cout << move_back_chars;
        std::this_thread::sleep_for(50ms);
    }
    
    move_back_chars.clear();
    
    move_back_chars = std::string(label.size(), '\b');
    move_back_chars += std::string(label.size(), ' ');
    move_back_chars += std::string(label.size(), '\b');
    
    std::cout << move_back_chars;
    
    std::cout << "[done]" << std::endl;
}
