//
// Created by Timothy Herchen on 2/7/18.
//

#ifndef VISUALIZATION_LINE_H
#define VISUALIZATION_LINE_H

#include <cstdlib>
#include <tuple>
#include <cmath>
#include <vector>
#include "../tests/print.h"

namespace Sine {
    namespace Graphics {
        namespace Algorithms {

            const int MAX_PIXELS_DRAWN = 500000;

            /**
             * Draw a line with thickness 1, no aliasing, between points (x1, y1) and (x2, y2).
             * @tparam Func Type of function to yield points to.
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param f Function to return results to (i.e. f(x, y) is called for every pixel to fill (x, y))
             */
            template<typename Func>
            inline void drawBresenham(int x1, int y1, int x2, int y2, Func f) {
                bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);

                if (steep) {
                    // The line is taller than it is wide, so we need to iterate over y

                    if (y1 > y2) {
                        // Put the points in a nice order

                        int temp = y2;
                        y2 = y1;
                        y1 = temp;

                        temp = x2;
                        x2 = x1;
                        x1 = temp;
                    }

                    int delta_x = std::abs(x2 - x1);
                    int delta_y = y2 - y1;

                    int error = 2 * delta_x - delta_y;

                    delta_y *= 2;
                    delta_x *= 2;

                    int x_change = (x2 < x1) ? -1 : 1;
                    int x = x1;

                    for (int y = y1; y <= y2; y++) {
                        f(x, y);
                        if (error > 0) {
                            x += x_change;
                            error -= delta_y;
                        }
                        error += delta_x;
                    }
                } else {
                    if (x1 > x2) {
                        // Put the points in a nice order

                        int temp = y2;
                        y2 = y1;
                        y1 = temp;

                        temp = x2;
                        x2 = x1;
                        x1 = temp;
                    }

                    int delta_x = x2 - x1;
                    int delta_y = std::abs(y2 - y1);

                    int error = 2 * delta_y - delta_x;

                    delta_x *= 2;
                    delta_y *= 2;

                    int y_change = (y2 < y1) ? -1 : 1;
                    int y = y1;

                    for (int x = x1; x <= x2; x++) {
                        f(x, y);
                        if (error > 0) {
                            y += y_change;
                            error -= delta_x;
                        }
                        error += delta_y;
                    }
                }
            }

            /**
             * Returns length of line segment squared.
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @return Length of segment (x1, y1) -- (x2, y2) squared.
             */
            float lineLengthSquared(int x1, int y1, int x2, int y2);

            /**
             * Returns length of line.
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @return Length of segment (x1, y1) -- (x2, y2).
             */
            float lineLength(int x1, int y1, int x2, int y2);

            float getCRatio(float c1, float c2, float c3);

            /**
             * Draws a thick line using Bresenham's algorithm (no antialiasing).
             *
             * The general strategy is to draw short lines with length @param thickness perpendicular to every pixel of a reference line that has thickness 1.
             * @tparam Func Type of functor which pixels are forwarded to.
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param thickness Thickness of line to be drawn.
             * @param f Function where pairs (x, y) are fed to.
             */
            template<typename Func>
            inline void drawBresenhamThick(int x1, int y1, int x2, int y2, float thickness, Func f) {
                // If the points are the same, this algorithm will be pregnant, so return
                if (x1 == x2 && y1 == y2) return;

                if (x1 < x2) {
                    std::swap(x1, x2);
                    std::swap(y1, y2);
                }

                thickness /= 2;
                thickness -= 0.01;

                // Length of given line
                float lineL = lineLength(x1, y1, x2, y2);

                // Find (x, y) delta of perpendicular line (e.g. (x1 + x_f, y1 - y_f) -- (x1 - x_f, y1 + y_f) is a line segment with length thickness and perpendicular to (x1, y1) -- (x2, y2))
                float x_f = thickness * (y1 - y2) / lineL;
                float y_f = thickness * (x1 - x2) / lineL;

                float minY, maxY;
                float linterY, rinterY;
                float minYx, maxYx;
                float linterYx, rinterYx;

                if (y_f > 0) {
                    if (y1 > y2) {
                        maxY = y1 + y_f;
                        minY = y2 - y_f;
                        maxYx = x1 - x_f;
                        minYx = x2 + x_f;
                        linterYx = x2 - x_f;
                        linterY = y2 + y_f;
                        rinterYx = x1 + x_f;
                        rinterY = y1 - y_f;
                    } else {
                        maxY = y2 + y_f;
                        minY = y1 - y_f;
                        maxYx = x2 - x_f;
                        minYx = x1 + x_f;
                        linterYx = x2 + x_f;
                        linterY = y2 - y_f;
                        rinterYx = x1 - x_f;
                        rinterY = y1 + y_f;
                    }
                } else {
                    if (y1 > y2) {
                        maxY = y1 - y_f;
                        maxYx = x1 + x_f;
                        minY = y2 + y_f;
                        minYx = x2 - x_f;
                        linterYx = x2 + x_f;
                        linterY = y2 - y_f;
                        rinterYx = x1 - x_f;
                        rinterY = y1 + y_f;
                    } else {
                        maxY = y2 - y_f;
                        minY = y1 + y_f;
                        maxYx = x1 + x_f;
                        minYx = x2 - x_f;
                        linterYx = x2 + x_f;
                        linterY = y2 - y_f;
                        rinterYx = x1 - x_f;
                        rinterY = y1 + y_f;
                    }
                }

                auto leftSide = [minY, minYx, linterYx, linterY, maxY, maxYx](int y) -> int {
                    if (y <= linterY) {
                        return int(getCRatio(y, minY, linterY) * (linterYx - minYx) + minYx);
                    } else {
                        return int(getCRatio(y, linterY, maxY) * (maxYx - linterYx) + linterYx);
                    }
                };

                auto rightSide = [minY, minYx, rinterYx, rinterY, maxY, maxYx](int y) -> int {
                    if (y <= rinterY) {
                        return int(getCRatio(y, minY, rinterY) * (rinterYx - minYx) + minYx);
                    } else {
                        return int(getCRatio(y, rinterY, maxY) * (maxYx - rinterYx) + rinterYx);
                    }
                };

                for (int y = minY; y <= maxY; y++) {
                    int rightS = rightSide(y);

                    for (int x = leftSide(y); x < rightS; x++) {
                        f(x, y);
                    }
                }
            }

            namespace {
                /**
                 * Derpy internal return type
                 */
                typedef std::tuple<float, float, float, float> _line;

                inline bool rejectLine(_line line) {
                    return (std::get<0>(line) == -1 || std::get<1>(line) == -1 || std::get<2>(line) == -1 ||
                            std::get<3>(line) == -1);
                }
            }

            /**
             * Trim line (x1, y1) -- (x2, y2) to be in rectangle (r_x1, r_y1) x (r_x2, r_y2).
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param r_x1 X coordinate of rectangle point 1.
             * @param r_y1 Y coordinate of rectangle point 1.
             * @param r_x2 X coordinate of rectangle point 2.
             * @param r_y2 Y coordinate of rectangle point 2.
             * @return _line in the format n_x1, n_y1, n_x2, n_y2
             */
            _line trimLine(float x1, float y1, float x2, float y2, float r_x1, float r_y1, float r_x2, float r_y2);

            /**
             * Draw Bresenham line, optimizing for parts of the line outside a rectangular boundary.
             * @tparam Func Type of functor to forward pixel pairs (x, y) to.
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param r_x1 X coordinate of rectangle point 1.
             * @param r_y1 Y coordinate of rectangle point 1.
             * @param r_x2 X coordinate of rectangle point 2.
             * @param r_y2 Y coordinate of rectangle point 2.
             * @param f Functor to forward pixel pairs (x, y) to.
             */
            template<typename Func>
            inline void
            drawMaskedBresenham(int x1, int y1, int x2, int y2, int r_x1, int r_y1, int r_x2, int r_y2, Func f) {
                auto line = trimLine(x1, y1, x2, y2, r_x1, r_y1, r_x2,
                                     r_y2); // Trim off parts of the line outside of the boundary

                if (rejectLine(line)) return;

                drawBresenham(std::get<0>(line), std::get<1>(line), std::get<2>(line), std::get<3>(line), f);
            }

            /**
             * Draw thick Bresenham line, optimizing for parts of the line outside a rectangular boundary.
             * @tparam Func Type of functor to forward pixel pairs (x, y) to.
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param thickness Thickness of line.
             * @param r_x1 X coordinate of rectangle point 1.
             * @param r_y1 Y coordinate of rectangle point 1.
             * @param r_x2 X coordinate of rectangle point 2.
             * @param r_y2 Y coordinate of rectangle point 2.
             * @param f Functor to forward pixel pairs (x, y) to.
             */
            template<typename Func>
            inline void
            drawMaskedBresenhamThick(int x1, int y1, int x2, int y2, float thickness, int r_x1, int r_y1, int r_x2,
                                     int r_y2, Func f) {
                if (r_x1 > r_x2)
                    std::swap(r_x1, r_x2);

                if (r_y1 > r_y2)
                    std::swap(r_y2, r_y2);

                // Trim off parts of the line outside of the boundary, with a margin of thickness
                auto line = trimLine(x1, y1, x2, y2, r_x1 - thickness, r_y1 - thickness, r_x2 + thickness,
                                     r_y2 + thickness);

                if (rejectLine(line)) return;

                drawBresenhamThick(std::get<0>(line), std::get<1>(line), std::get<2>(line), std::get<3>(line),
                                   thickness, f);
            }

            /**
             * Return whether a line is vertical.
             * @param x1 X coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @return Whether the line is vertical.
             */
            bool isVertical(int x1, int, int x2, int);

            /**
             * Return whether a line is horizontal.
             * @param y1 Y coordinate of point 1.
             * @param y2 Y coordinate of point 2.
             * @return Whether the line is horizontal.
             */
            bool isHorizontal(int, int y1, int, int y2);

            /**
             * Return the Y coordinate of the point with x coordinate x_sample on the line (x1, y1) -- (x2, y2).
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param x_sample X coordinate of "sampled" point
             * @return Y coordinate of point
             */
            float lineYAt(int x1, int y1, int x2, int y2, int x_sample);

            /**
             * Return the X coordinate of the point with y coordinate y_sample on the line (x1, y1) -- (x2, y2).
             * @param x1 X coordinate of point 1.
             * @param y1 Y coordinate of point 1.
             * @param x2 X coordinate of point 2.
             * @param y2 Y coordinate of point 2.
             * @param y_sample Y coordinate of "sampled" point
             * @return X coordinate of point
             */
            float lineXAt(int x1, int y1, int x2, int y2, int y_sample);

            /*
             * Algorithm credit to https://gist.github.com/randvoorhies/807ce6e20840ab5314eb7c547899de68
             */

            /**
             * Draw an anti-aliased line with Xiaolin's algorithm.
             * @tparam Func Type of functor to be called
             * @param x1 X coordinate of point 1
             * @param y1 Y coordinate of point 1
             * @param x2 X coordinate of point 2
             * @param y2 Y coordinate of point 2
             * @param f Functor to be called as f(x, y, brightness)
             */
            template<typename Func>
            inline void drawXiaolin(float x1, float y1, float x2, float y2, Func f) {
                if (x1 > x2) {
                    std::swap(x1, x2);
                    std::swap(y1, y2);
                }

                float d_x = std::abs(x2 - x1);
                float x_d = x1 < x2 ? 1 : -1;
                float d_y = std::abs(y2 - y1);

                float e_d = ((d_x + d_y == 0) ? 1 : std::sqrt(d_x * d_x + d_y * d_y));
                float y_d = y1 < y2 ? 1 : -1;
                float error = d_x - d_y;
                float e2, x3;

#define gen_L(op) while (true) { \
                    f(x1, y1, 255 * std::abs(error - d_x + d_y) / e_d); \
                    e2 = error; \
                    x3 = x1; \
                    if (2 * e2 >= -d_x) { \
                        if (x1 >= x2) { \
                            break; \
                        } \
                        if (d_y + e2 <= e_d) { \
                            f(x1, y1 + y_d, 255 * (e2 + d_y) / e_d); \
                        } \
 \
                        x1 += x_d; \
                        error -= d_y; \
                    } \
                    if (2 * e2 <= d_y) { \
                        if (y1 op y2) { \
                            break; \
                        } \
                        if (d_x - e2 <= e_d) { \
                            f(x3 + x_d, y1, 255 * (d_x - e2) / e_d); \
                        } \
 \
                        y1 += y_d; \
                        error += d_x; \
                    } \
                }

                if (y1 < y2) {
                    gen_L(>=)
                } else {
                    gen_L(<=)
                }
            }

            template<typename Func>
            inline void
            drawMaskedXiaolin(int x1, int y1, int x2, int y2, int r_x1, int r_y1, int r_x2,
                              int r_y2, Func f) {
                if (r_x1 > r_x2)
                    std::swap(r_x1, r_x2);

                if (r_y1 > r_y2)
                    std::swap(r_y2, r_y2);

                // Trim off parts of the line outside of the boundary, with a margin of thickness
                auto line = trimLine(x1, y1, x2, y2, r_x1, r_y1, r_x2, r_y2);

                if (rejectLine(line)) return;

                drawXiaolin(std::get<0>(line), std::get<1>(line), std::get<2>(line), std::get<3>(line), f);
            }

            /*
             * Algorithm credit to https://gist.github.com/randvoorhies/807ce6e20840ab5314eb7c547899de68
             */

            /**
             * Draw a thick anti-aliased line. Note that the line will not have a perpendicular ending edge, unlike the thick bresenham.
             *
             * @tparam Func Type of functor to be called
             * @param x1 X coordinate of point 1
             * @param y1 Y coordinate of point 1
             * @param x2 X coordinate of point 2
             * @param y2 Y coordinate of point 2
             * @param thickness Thickness of line
             * @param f Functor to be called as f(x, y, brightness)
             */
            template<typename Func>
            inline void drawXiaolinThick(float x1, float y1, float x2, float y2, float thickness, Func f) {
                float d_x = std::abs(x2 - x1), x_d = x1 < x2 ? 1 : -1;
                float d_y = std::abs(y2 - y1), y_d = y1 < y2 ? 1 : -1;
                float error;
                float length = std::sqrt(d_x * d_x + d_y * d_y);

                if (thickness <= 1 || length == 0) {
                    drawXiaolin(x1, y1, x2, y2, f);
                    return;
                }

                d_x *= 255 / length;
                d_y *= 255 / length;
                thickness = 255 * (thickness - 1);

                if (d_x < d_y) {
                    x2 = std::round((length + thickness / 2) / d_y);
                    error = x2 * d_y - thickness / 2;
                    if (y1 < y2) {
                        for (x1 -= x2 * x_d;; y1 += y_d) {
                            f(x2 = x1, y1, error);
                            for (length = d_y - error - thickness; length + d_y < 255; length += d_y) {
                                f(x2 += x_d, y1, 0);
                            }
                            f(x2 + x_d, y1, length);
                            if (y1 >= y2) {
                                break;
                            }
                            error += d_x;
                            if (error > 255) {
                                error -= d_y;
                                x1 += x_d;
                            }
                        }
                    } else {
                        for (x1 -= x2 * x_d;; y1 += y_d) {
                            f(x2 = x1, y1, error);
                            for (length = d_y - error - thickness; length + d_y < 255; length += d_y) {
                                f(x2 += x_d, y1, 0);
                            }
                            f(x2 + x_d, y1, length);
                            if (y1 <= y2) {
                                break;
                            }
                            error += d_x;
                            if (error > 255) {
                                error -= d_y;
                                x1 += x_d;
                            }
                        }
                    }
                } else {
                    y2 = std::round((length + thickness / 2) / d_x);
                    error = y2 * d_x - thickness / 2;

                    y1 -= y2 * y_d;

                    if (x1 > x2) {
                        while (true) {
                            y2 = y1;
                            f(x1, y2, error);
                            for (length = d_x - error - thickness; length + d_x < 255; length += d_x) {
                                y2 += y_d;
                                f(x1, y2, 0);
                            }
                            f(x1, y2 + y_d, length);
                            if (x1 <= x2) {
                                break;
                            }
                            error += d_y;
                            if (error > 255) {
                                error -= d_x;
                                y1 += y_d;
                            }

                            x1 += x_d;
                        }
                    } else {
                        while (true) {
                            y2 = y1;
                            f(x1, y2, error);
                            for (length = d_x - error - thickness; length + d_x < 255; length += d_x) {
                                y2 += y_d;
                                f(x1, y2, 0);
                            }
                            f(x1, y2 + y_d, length);
                            if (x1 >= x2) {
                                break;
                            }
                            error += d_y;
                            if (error > 255) {
                                error -= d_x;
                                y1 += y_d;
                            }

                            x1 += x_d;
                        }
                    }
                }
            }

            template<typename Func>
            inline void
            drawMaskedXiaolinThick(int x1, int y1, int x2, int y2, float thickness, int r_x1, int r_y1, int r_x2,
                                   int r_y2, Func f) {
                if (r_x1 > r_x2)
                    std::swap(r_x1, r_x2);

                if (r_y1 > r_y2)
                    std::swap(r_y2, r_y2);

                // Trim off parts of the line outside of the boundary, with a margin of thickness
                auto line = trimLine(x1, y1, x2, y2, r_x1 - thickness, r_y1 - thickness, r_x2 + thickness,
                                     r_y2 + thickness);

                if (rejectLine(line)) return;

                drawXiaolinThick(std::get<0>(line), std::get<1>(line), std::get<2>(line), std::get<3>(line),
                                 thickness, f);
            }
        }
    }
}

#endif //VISUALIZATION_LINE_H
