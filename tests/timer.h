//
// Created by Timothy Herchen on 2/3/18.
//

#ifndef VISUALIZATION_TIMER_H
#define VISUALIZATION_TIMER_H

#include <chrono>

namespace Sine::General {
    typedef std::chrono::seconds seconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::nanoseconds nanoseconds;

    /**
     * Sine::Timer is an automatic, scope-bound Timer.
     *
     * Its constructor starts an internal clock and whose destructor outputs the duration since construction.
     * As such, it times the length of a scope.
     *
     * @tparam T Unit measured (Sine::seconds, Sine::milliseconds, Sine::microseconds, Sine::nanoseconds).
     */

    template<typename T = milliseconds>
    class Timer {
    private:
        using timestamp = decltype(std::chrono::high_resolution_clock::now());

        long *time_ref;
        std::string id;

        timestamp start;
        timestamp end;
    public:
        /**
         * Default constructor.
         */
        Timer();

        /**
         * Constructor given a reference to long, which is written to at destruction.
         * @param output Reference to long int.
         */
        explicit Timer(long &output);

        /**
         * Constructor given a std::string, which is printed out to std::cout along with the time elapsed at destruction.
         * @param id Output id.
         */
        explicit Timer(const std::string &id);

        /**
         * Internal method to get a string representation of the unit (e.g. ms for milliseconds).
         * @return String representation of @tparam T.
         */
        static std::string getUnit();

        /**
         * Destructor which handles output to std::cout.
         */
        ~Timer();
    };

    typedef Timer<milliseconds> DefaultTimer;
}


#endif //VISUALIZATION_TIMER_H
