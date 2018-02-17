//
// Created by Timothy Herchen on 2/16/18.
//

#ifndef VISUALIZATION_CIRCLE_H
#define VISUALIZATION_CIRCLE_H

#include "line.h"

namespace Sine::Graphics::Algorithms {
    template<typename Func>
    void drawCircle(int xm, int ym, int r, Func f) {
        int x = -r, y = 0, err = 2 - 2 * r;                /* bottom left to top right */
        do {
            f(xm - x, ym + y);                            /*   I. Quadrant +x +y */
            f(xm - y, ym - x);                            /*  II. Quadrant -x +y */
            f(xm + x, ym - y);                            /* III. Quadrant -x -y */
            f(xm + y, ym + x);                            /*  IV. Quadrant +x -y */
            r = err;
            if (r <= y) err += ++y * 2 + 1;                                   /* y step */
            if (r > x || err > y) err += ++x * 2 + 1;                         /* x step */
        } while (x < 0);
    }

    template<typename Func>
    inline void drawCircleAntialiased(float xm, float ym, float r, Func f) {
        float x = r, y = 0;
        float i, x2, e2, err = 2 - 2 * r;
        r = 1 - err;
        while (true) {
            i = 255 * std::abs(err + 2 * (x + y) - 2) / r;
            f(xm + x, ym - y, i);
            f(xm + y, ym + x, i);
            f(xm - x, ym + y, i);
            f(xm - y, ym - x, i);
            if (x == 0) break;
            e2 = err;
            x2 = x;
            if (err > y) {
                i = 255 * (err + 2 * x - 1) / r;
                if (i < 255) {
                    f(xm + x, ym - y + 1, i);
                    f(xm + y - 1, ym + x, i);
                    f(xm - x, ym + y - 1, i);
                    f(xm - y + 1, ym - x, i);
                }
                err -= --x * 2 - 1;
            }
            if (e2 <= x2--) {
                i = 255 * (1 - 2 * y - e2) / r;
                if (i < 255) {
                    f(xm + x2, ym - y, i);
                    f(xm + y, ym + x2, i);
                    f(xm - x2, ym + y, i);
                    f(xm - y, ym - x2, i);
                }
                err -= --y * 2 - 1;
            }
        }
    }

    template<typename Func>
    void drawFilledCircle(int xm, int ym, int r, Func f) {

    }
}


#endif //VISUALIZATION_CIRCLE_H
