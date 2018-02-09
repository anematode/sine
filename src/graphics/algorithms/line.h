//
// Created by Timothy Herchen on 2/7/18.
//

#ifndef VISUALIZATION_LINE_H
#define VISUALIZATION_LINE_H

#include <cstdlib>
#include <tuple>
#include <cmath>

namespace Sine {
    namespace Graphics {
        namespace Algorithms {
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
            void drawBresenham(int x1, int y1, int x2, int y2, Func f) {
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

                    int x_change = (x2 < x1) ? -1 : 1;
                    int x = x1;

                    for (int y = y1; y <= y2; y++) {
                        f(x, y);
                        if (error > 0) {
                            x += x_change;
                            error -= 2 * delta_y;
                        }
                        error += 2 * delta_x;
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

                    int y_change = (y2 < y1) ? -1 : 1;
                    int y = y1;

                    for (int x = x1; x <= x2; x++) {
                        f(x, y);
                        if (error > 0) {
                            y += y_change;
                            error -= 2 * delta_x;
                        }
                        error += 2 * delta_y;
                    }
                }
            }

            /**
             * Derpy internal return type
             */
            typedef std::tuple<int, int, int, int> _line;

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
            _line trimLine(int x1, int y1, int x2, int y2, int r_x1, int r_y1, int r_x2, int r_y2);

            template<typename Func>
            void drawMaskedBresenham(int x1, int y1, int x2, int y2, int r_x1, int r_y1, int r_x2, int r_y2, Func f) {
                auto line = trimLine(x1, y1, x2, y2, r_x1, r_y1, r_x2, r_y2);

                drawBresenham(std::get<0>(line), std::get<1>(line), std::get<2>(line), std::get<3>(line), f);
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
        }
    }
}

#endif //VISUALIZATION_LINE_H
