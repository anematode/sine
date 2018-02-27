//
// Created by Timothy Herchen on 2/16/18.
//

#ifndef VISUALIZATION_CIRCLE_H
#define VISUALIZATION_CIRCLE_H

#include <thread>
#include "line.h"

namespace Sine::Graphics::Algorithms {
    /*
     * Algorithm credit to https://gist.github.com/randvoorhies/807ce6e20840ab5314eb7c547899de68
     */

    template<typename Func>
    void drawCircle(int xm, int ym, int r, Func f) {
        int x = -r, y = 0, err = 2 - 2 * r;
        do {
            f(xm - x, ym + y);
            f(xm - y, ym - x);
            f(xm + x, ym - y);
            f(xm + y, ym + x);
            r = err;
            if (r <= y) err += ++y * 2 + 1;
            if (r > x || err > y) err += ++x * 2 + 1;
        } while (x < 0);
    }

    /*
     * Algorithm credit to https://gist.github.com/randvoorhies/807ce6e20840ab5314eb7c547899de68
     */
    
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
    inline void drawFilledCircle(int xm, int ym, int r, Func f) {
        int r_sq = r * r;

        int x_i = r;

        for (int x = xm - r; x < xm; x++, x_i--) {
            int y_d = std::sqrt(r_sq - x_i * x_i);

            for (int y = ym - y_d; y < ym; y++) {
                f(x, y);
                f(x, 2 * ym - y);
                f(2 * xm - x, y);
                f(2 * xm - x, 2 * ym - y);
            }
        }

        for (int y = ym - r; y < ym + r; y++) {
            f(xm, y);
        }

        for (int x = xm - r; x < xm + r; x++) {
            f(x, ym);
        }
    }
}


#endif //VISUALIZATION_CIRCLE_H
