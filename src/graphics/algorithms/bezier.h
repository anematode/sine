//
// Created by Timothy Herchen on 2/14/18.
//

#ifndef VISUALIZATION_BEZIER_H
#define VISUALIZATION_BEZIER_H


#include "line.h"

namespace Sine::Graphics::Algorithms {
    /**
     * Bezier algorithms from https://gist.github.com/randvoorhies/807ce6e20840ab5314eb7c547899de68
     */
    template<typename Func>
    inline void drawQuadraticBezierSegment(float x0, float y0, float x1, float y1, float x2, float y2, Func f) {
        float sx = x2 - x1, sy = y2 - y1;
        float xx = x0 - x1, yy = y0 - y1, xy;
        float dx, dy, err, cur = xx * sy - yy * sx;

        if (sx * sx + sy * sy > xx * xx + yy * yy) {
            x2 = x0;
            x0 = sx + x1;
            y2 = y0;
            y0 = sy + y1;
            cur = -cur;
        }

        int iters = MAX_PIXELS_DRAWN;

        if (cur != 0) {
            xx += sx;
            xx *= sx = x0 < x2 ? 1 : -1;
            yy += sy;
            yy *= sy = y0 < y2 ? 1 : -1;
            xy = 2 * xx * yy;
            xx *= xx;
            yy *= yy;
            if (cur * sx * sy < 0) {
                xx = -xx;
                yy = -yy;
                xy = -xy;
                cur = -cur;
            }
            dx = 4.0 * sy * cur * (x1 - x0) + xx - xy;
            dy = 4.0 * sx * cur * (y0 - y1) + yy - xy;
            xx += xx;
            yy += yy;
            err = dx + dy + xy;
            do {
                f(x0, y0);
                if ((((sx < 0) && x0 <= x2) || ((sx > 0) && x0 >= x2)) &&
                    (((sy < 0) && y0 <= y2) || ((sy > 0) && y0 >= y2)))
                    return; //
                y1 = 2 * err < dx;
                if (2 * err > dy) {
                    x0 += sx;
                    dx -= xy;
                    err += dy += yy;
                }
                if (y1) {
                    y0 += sy;
                    dy -= xy;
                    err += dx += xx;
                }
            } while (dy < 0 && dx > 0 && --iters >= 0);
        }
        drawBresenham(x0, y0, x2, y2, f);
    }

    template<typename Func>
    inline void drawQuadraticBezier(float x0, float y0, float x1, float y1, float x2, float y2, Func f) {
        if (std::isnan(x0) || std::isnan(y0) || std::isnan(x1) || std::isnan(y1) || std::isnan(x2) || std::isnan(y2)) {
            return;
        }

        float x = x0 - x1, y = y0 - y1, t = x0 - 2 * x1 + x2, r;

        if (x * (x2 - x1) > 0) {
            if (y * (y2 - y1) > 0) {
                if (std::abs((y0 - 2 * y1 + y2) / t * x) > std::abs(y)) {
                    x0 = x2;
                    x2 = x + x1;
                    y0 = y2;
                    y2 = y + y1;
                }
            }
            t = (x0 - x1) / t;
            r = (1 - t) * ((1 - t) * y0 + 2.0 * t * y1) + t * t * y2;
            t = (x0 * x2 - x1 * x1) * t / (x0 - x1);
            x = std::floor(t + 0.5);
            y = std::floor(r + 0.5);
            r = (y1 - y0) * (t - x0) / (x1 - x0) + y0;
            drawQuadraticBezierSegment(x0, y0, x, std::floor(r + 0.5), x, y, f);
            r = (y1 - y2) * (t - x2) / (x1 - x2) + y2;
            x0 = x1 = x;
            y0 = y;
            y1 = std::floor(r + 0.5);
        }
        if ((y0 - y1) * (y2 - y1) > 0) {
            t = y0 - 2 * y1 + y2;
            t = (y0 - y1) / t;
            r = (1 - t) * ((1 - t) * x0 + 2.0 * t * x1) + t * t * x2;
            t = (y0 * y2 - y1 * y1) * t / (y0 - y1);
            x = std::floor(r + 0.5);
            y = std::floor(t + 0.5);
            r = (x1 - x0) * (t - y0) / (y1 - y0) + x0;
            drawQuadraticBezierSegment(x0, y0, std::floor(r + 0.5), y, x, y, f);
            r = (x1 - x2) * (t - y2) / (y1 - y2) + x2;
            x0 = x;
            x1 = std::floor(r + 0.5);
            y0 = y1 = y;
        }
        drawQuadraticBezierSegment(x0, y0, x1, y1, x2, y2, f);
    }


    template<typename Func>
    void drawQuadraticBezierSegmentAntialiased(float x0, float y0, float x1, float y1, float x2, float y2, Func f) {
        float sx = x2 - x1, sy = y2 - y1;
        float xx = x0 - x1, yy = y0 - y1, xy;
        float dx, dy, err, ed, cur = xx * sy - yy * sx;

        if (sx * sx + sy * sy > xx * xx + yy * yy) {
            x2 = x0;
            x0 = sx + x1;
            y2 = y0;
            y0 = sy + y1;
            cur = -cur;
        }

        if (cur != 0) {
            xx += sx;
            xx *= sx = x0 < x2 ? 1 : -1;
            yy += sy;
            yy *= sy = y0 < y2 ? 1 : -1;
            xy = 2 * xx * yy;
            xx *= xx;
            yy *= yy;
            if (cur * sx * sy < 0) {
                xx = -xx;
                yy = -yy;
                xy = -xy;
                cur = -cur;
            }
            dx = 4.0 * sy * (x1 - x0) * cur + xx - xy;
            dy = 4.0 * sx * (y0 - y1) * cur + yy - xy;
            xx += xx;
            yy += yy;
            err = dx + dy + xy;
            do {
                cur = std::min(dx + xy, -xy - dy);
                ed = std::max(dx + xy, -xy - dy);
                ed += 2 * ed * cur * cur / (4 * ed * ed + cur * cur);
                f(x0, y0, 255 * std::abs(err - dx - dy - xy) / ed);
                if (x0 == x2 || y0 == y2) break;
                x1 = x0;
                cur = dx - err;
                y1 = 2 * err + dy < 0;
                if (2 * err + dx > 0) {
                    if (err - dy < ed) {
                        f(x0, y0 + sy, 255 * std::abs(err - dy) / ed);
                    }
                    x0 += sx;
                    dx -= xy;
                    err += dy += yy;
                }
                if (y1) {
                    if (cur < ed) {
                        f(x1 + sx, y0, 255 * std::abs(cur) / ed);
                    }
                    y0 += sy;
                    dy -= xy;
                    err += dx += xx;
                }
            } while (dy < dx);
        }
        drawXiaolin(x0, y0, x2, y2, f);
    }

    template<typename Func>
    void drawQuadraticBezierAntialiased(float x0, float y0, float x1, float y1, float x2, float y2, Func f) {
        float x = x0 - x1, y = y0 - y1, t = x0 - 2 * x1 + x2, r;

        if (x * (x2 - x1) > 0) {
            if (y * (y2 - y1) > 0) {
                if (std::abs((y0 - 2 * y1 + y2) / t * x) > std::abs(y)) {
                    x0 = x2;
                    x2 = x + x1;
                    y0 = y2;
                    y2 = y + y1;
                }
            }
            t = (x0 - x1) / t;
            r = (1 - t) * ((1 - t) * y0 + 2.0 * t * y1) + t * t * y2;
            t = (x0 * x2 - x1 * x1) * t / (x0 - x1);
            x = std::floor(t + 0.5);
            y = std::floor(r + 0.5);
            r = (y1 - y0) * (t - x0) / (x1 - x0) + y0;
            drawQuadraticBezierSegmentAntialiased(x0, y0, x, std::floor(r + 0.5), x, y, f);
            r = (y1 - y2) * (t - x2) / (x1 - x2) + y2;
            x0 = x1 = x;
            y0 = y;
            y1 = std::floor(r + 0.5);
        }
        if ((y0 - y1) * (y2 - y1) > 0) {
            t = y0 - 2 * y1 + y2;
            t = (y0 - y1) / t;
            r = (1 - t) * ((1 - t) * x0 + 2.0 * t * x1) + t * t * x2;
            t = (y0 * y2 - y1 * y1) * t / (y0 - y1);
            x = std::floor(r + 0.5);
            y = std::floor(t + 0.5);
            r = (x1 - x0) * (t - y0) / (y1 - y0) + x0;
            drawQuadraticBezierSegmentAntialiased(x0, y0, std::floor(r + 0.5), y, x, y, f);
            r = (x1 - x2) * (t - y2) / (y1 - y2) + x2;
            x0 = x;
            x1 = std::floor(r + 0.5);
            y0 = y1 = y;
        }
        drawQuadraticBezierSegmentAntialiased(x0, y0, x1, y1, x2, y2, f);
    }
}
#endif //VISUALIZATION_BEZIER_H
