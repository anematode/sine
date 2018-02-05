//
// Created by Timothy Herchen on 2/2/18.
//

#ifndef VISUALIZATION_LINE_H
#define VISUALIZATION_LINE_H

#include <cmath>

namespace Sine::Math {

    // TODO: Implement
    template<typename T>
    class Line {
    public:
        int x1, y1, x2, y2;

        Line(T _x1, T _y1, T _x2, T _y2);

        double length();

        ~Line();
    };

    template<typename T>
    Line::Line(T _x1, T _y1, T _x2, T _y2) {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }

    template<typename T>
    Line::~Line() {

    }

    template<typename T>
    T Line<T>::length() {
        return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

}


#endif //VISUALIZATION_LINE_H
