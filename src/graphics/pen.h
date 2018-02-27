//
// Created by Timothy Herchen on 2/16/18.
//

#ifndef VISUALIZATION_PEN_H
#define VISUALIZATION_PEN_H

namespace Sine::Graphics {
    struct Pen {
        RGBA color;
        RGBA fillcolor;
        double width;

        explicit Pen(const RGBA &_color = Colors::BLACK, int _width = 1, const RGBA &_fillcolor = Colors::BLACK) {
            color = _color;
            width = _width;
            fillcolor = _fillcolor;
        }
    };

    inline Pen BlackPen{}, BluePen{Colors::BLUE}, RedPen{Colors::RED}, GreenPen{Colors::GREEN}, WhitePen{
            Colors::WHITE}, Sharpie{Colors::BLACK, 5};
}

#endif //VISUALIZATION_PEN_H
