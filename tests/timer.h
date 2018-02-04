//
// Created by Timothy Herchen on 2/3/18.
//

#ifndef VISUALIZATION_TIMER_H
#define VISUALIZATION_TIMER_H

#include <chrono>

namespace Sine {
    typedef std::chrono::seconds seconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::nanoseconds nanoseconds;

    template<typename T = milliseconds>
    class Timer {
    private:
        using timestamp = decltype(std::chrono::high_resolution_clock::now());

        long *time_ref;
        std::string id;

        timestamp start;
        timestamp end;
    public:

        Timer();

        explicit Timer(long &microseconds);

        explicit Timer(const std::string &id);

        std::string getUnit();

        ~Timer();
    };

    typedef Timer<milliseconds> DefaultTimer;
}


#endif //VISUALIZATION_TIMER_H
