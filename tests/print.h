//
// Created by Timothy Herchen on 2/15/18.
//

#ifndef VISUALIZATION_PRINT_H
#define VISUALIZATION_PRINT_H

#include <iostream>

namespace Sine::General {
    template<typename Arg, typename... Args>
    inline void print(Arg &&arg, Args &&... args) {
        std::cout << std::forward<Arg>(arg);
        using expander = int[];
        (void) expander{0, (void(std::cout << ',' << std::forward<Args>(args)), 0)...};
    }

    template<typename Arg, typename... Args>
    inline void printLine(Arg &&arg, Args &&... args) {
        print(arg, args...);
        std::cout << '\n';
    }
}

#endif //VISUALIZATION_PRINT_H
