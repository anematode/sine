//
// Created by Timothy Herchen on 2/3/18.
//

#include <string>
#include <iostream>
#include "timer.h"

namespace Sine {
    template<typename T>
    Timer<T>::Timer() : time_ref(nullptr), id("") {
        start = std::chrono::high_resolution_clock::now();
    }

    template<typename T>
    Timer<T>::Timer(long &time) : time_ref(&time) {
        start = std::chrono::high_resolution_clock::now();
    }

    template<typename T>
    Timer<T>::Timer(const std::string &_id) : time_ref(nullptr), id(_id) {
        start = std::chrono::high_resolution_clock::now();
    }

    template<typename T>
    std::string Timer<T>::getUnit() {
        return "";
    }

    template<>
    std::string Timer<std::chrono::seconds>::getUnit() {
        return "s";
    }

    template<>
    std::string Timer<std::chrono::milliseconds>::getUnit() {
        return "ms";
    }

    template<>
    std::string Timer<std::chrono::microseconds>::getUnit() {
        return "us";
    }

    template<>
    std::string Timer<std::chrono::nanoseconds>::getUnit() {
        return "ns";
    }

    template<typename T>
    Timer<T>::~Timer() {
        end = std::chrono::high_resolution_clock::now();

        long delta = std::chrono::duration_cast<T>(end - start).count();

        if (time_ref) {
            *time_ref = delta;
        } else {
            if (!id.empty()) {
                std::cout << id << ": ";
            }
            std::cout << delta << ' ' << getUnit() << '\n';
        }
    }

    template
    class Timer<seconds>;

    template
    class Timer<milliseconds>;

    template
    class Timer<microseconds>;

    template
    class Timer<nanoseconds>;
}