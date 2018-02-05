#ifndef GAUSSIAN_BLUR_DEFINED_
#define GAUSSIAN_BLUR_DEFINED_

#include "filter.h"
#include <iostream>
#include <limits>

namespace Sine::Graphics {
    namespace Filters {
        namespace {

            /**
             * Returns x ^ y.
             * @param x x
             * @param y y
             * @return x ^ y
             */
            constexpr double pow(double x, int y) {
                return y == 0 ? 1.0 : x * pow(x, y - 1);
            }

            /**
             * Returns x!.
             * @param x x
             * @return x!
             */
            constexpr int factorial(int x) { return x == 0 ? 1 : x * factorial(x - 1); }

            /**
             * Returns e^x.
             * @param x x
             * @return e^x
             */
            constexpr double c_exp(double x) {
                return (x < -8)
                       ? 0
                       : ((x < 0)
                          ? (1 / c_exp(-x))
                          : 1.0 + x + pow(x, 2) / factorial(2) +
                            pow(x, 3) / factorial(3) + pow(x, 4) / factorial(4) +
                            pow(x, 5) / factorial(5) + pow(x, 6) / factorial(6) +
                            pow(x, 7) / factorial(7) + pow(x, 8) / factorial(8) +
                            pow(x, 9) / factorial(9));
            }

            /**
             * Internal sqrt stuff from https://stackoverflow.com/a/34134071/7333670.
             * @param x no clue
             * @param curr no clue
             * @param prev no clue
             * @return no clue
             */
            double constexpr sqrtNewtonRaphson(double x, double curr, double prev) {
                return curr == prev ? curr
                                    : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
            }

            /**
             * sqrt from https://stackoverflow.com/a/34134071/7333670.
             * @param x x
             * @return sqrt(x)
             */
            double constexpr c_sqrt(double x) {
                return x >= 0 && x < std::numeric_limits<double>::infinity()
                       ? sqrtNewtonRaphson(x, x, 0)
                       : std::numeric_limits<double>::quiet_NaN();
            }

            /**
             * Constants which effectively allow Gaussian to be integral rather than float.
             */
            const int MULT_FACTOR_LOG2 = 13;
            const int MULT_FACTOR = 2 << MULT_FACTOR_LOG2;

            /**
             * Returns the magnitude of a 1d Gaussian with stddev stddevs100 / 100.
             * @param index Index of the Gaussian.
             * @param stddevs100 stddev * 100.
             * @return Value of Gaussian at index.
             */
            constexpr int getGFactor(size_t index, int stddevs100) {
                return static_cast<int>(MULT_FACTOR *
                                        c_exp(-((int) index * (int) index) / (stddevs100 / 100.0)) /
                                        c_sqrt(3.14159265358979 * stddevs100 / 100.0));
            }

            /**
             * Struct which holds args.
             * @tparam args arguments
             */
            template<unsigned... args>
            struct ArrayHolder {
                static const unsigned int data[sizeof...(args)];
            };

            /**
             * Struct which holds const args.
             * @tparam args arguments
             */
            template<const unsigned... args>
            const unsigned int ArrayHolder<args...>::data[sizeof...(args)] = {args...};

            /**
             * Template metaprogramming helper.
             * @tparam N number
             * @tparam L stddev * 100
             * @tparam F MetaFunc
             * @tparam args arguments getting peeled, or, I guess, the reverse of peeled
             */
            template<size_t N, int L, template<size_t, int> class F, const unsigned int... args>
            struct generate_array_rec {
                typedef
                typename generate_array_rec<N - 1, L, F, F<N, L>::value, args...>::result
                        result;
            };

            // Specialization for TMP
            template<template<size_t, int> class F, int L, const unsigned int... args>
            struct generate_array_rec<0, L, F, args...> {
                typedef ArrayHolder<F<0, L>::value, args...> result;
            };

            /**
             * Template metaprogramming helper, marks "entrance" into peeling operation
             * @tparam N number
             * @tparam L stddev * 100
             * @tparam F MetaFunc
             */
            template<size_t N, int L, template<size_t, int> class F>
            struct generate_array {
                typedef typename generate_array_rec<N - 1, L, F>::result result;
            };

            /**
             * Template metaprogramming helper, encapsulating result of gaussian function
             * @tparam index Index of Gaussian
             * @tparam stddevs100 stddev * 100
             */
            template<size_t index, int stddevs100>
            struct MetaFunc {
                enum {
                    value = getGFactor(index, stddevs100)
                };
            };

            /**
             * Sums an array recursively
             * @param array Array to sum
             * @param pos_first_elem Position of first element
             * @param pos_last_elem Position of last element
             * @return Sum of array
             */
            constexpr unsigned long sum(const unsigned int array[], int pos_first_elem, int pos_last_elem) {
                return (pos_first_elem == pos_last_elem) ? array[pos_first_elem] : array[pos_first_elem] +
                                                                                   sum(array, pos_first_elem + 1,
                                                                                       pos_last_elem);
            }

        };

        /**
         * Gaussian Blur Filter.
         * @tparam size Radius of the blur.
         */
        template<unsigned int size>
        class GaussianBlur : public Filter {
        private:
            /**
             * Internal gaussian array.
             */
            typedef typename generate_array<
                    size + 1, 50 * size, MetaFunc>::result gaussian_gen;
            /**
             * Scale factor of gaussian array.
             */
            static unsigned long denominator;

        public:
            void applyTo(Bitmap &map);

            void applyTo(Graymap &map);

            void applyTo(RGBMap &map);

            void applyTo(RGBAMap &map);

            /**
             * Silly testing function to print out the internal gaussian array.
             */
            void print();
        };

        template<unsigned int size>
        void GaussianBlur<size>::print() {
            for (int i = 0; i < size; i++) {
                std::cout << gaussian_gen::data[i] << ' ';
            }
        }

        // Calculate denominator based on sum of gaussian_gen
        template<unsigned int size>
        unsigned long GaussianBlur<size>::denominator =
                sum(gaussian_gen::data, 1, size + 1) * 2 + gaussian_gen::data[0];

        // The general blur strategy is to go in two passes, one vertical and the other horizontal.
        // The properties of the gaussian blur make this possible. This reduces computational complexity
        // from O(4whr^2) to O(2whr), where w is width, h is height, and r is the blur radius.

        template<unsigned int size>
        void GaussianBlur<size>::applyTo(Bitmap &map) {
            int width = map.getWidth();
            int height = map.getHeight();
            int size_nu = size;

            bool a[std::max(width, height)]; // Buffer which holds the current row or column, should fit in cache...

            for (int y_s = 0; y_s < height; y_s++) {
                for (int x_s = 0; x_s < width; x_s++) { // Fill up the buffer with a row
                    a[x_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int x_s = 0; x_s < width; x_s++) {
                    long graySum = 0;
                    int multiplier;

                    for (int x_f = std::max(0, x_s - size_nu), loc = x_f - x_s;
                         x_f <=
                         std::min(width - 1, x_s + size_nu); x_f++, loc++) { // Pretty liberal usage of , operator eh
                        multiplier = gaussian_gen::data[std::abs(loc)]; // Weighted sum based on Gaussian function

                        graySum += a[x_f] ? 0 : 256 * multiplier;
                    }

                    graySum /= denominator; // Find average

                    map.setPixelUnsafe(x_s, y_s, (graySum < 128)); // Pixel output
                }
            }

            for (int x_s = 0; x_s < width; x_s++) {
                for (int y_s = 0; y_s < height; y_s++) { // Fill up the buffer with a column
                    a[y_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int y_s = 0; y_s < height; y_s++) {
                    long graySum = 0;
                    int multiplier;

                    for (int y_f = std::max(0, y_s - size_nu), loc = y_f - y_s;
                         y_f <= std::min(width - 1, y_s + size_nu); y_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        graySum += a[y_f] ? 0 : 256 * multiplier;
                    }

                    graySum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, (graySum < 128));
                }
            }
        }

        template<unsigned int size>
        void GaussianBlur<size>::applyTo(Graymap &map) {
            int width = map.getWidth();
            int height = map.getHeight();
            int size_nu = size;

            unsigned char a[std::max(width, height)];

            for (int y_s = 0; y_s < height; y_s++) {
                for (int x_s = 0; x_s < width; x_s++) {
                    a[x_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int x_s = 0; x_s < width; x_s++) {
                    long graySum = 0;
                    int multiplier;

                    for (int x_f = std::max(0, x_s - size_nu), loc = x_f - x_s;
                         x_f <= std::min(width - 1, x_s + size_nu); x_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        graySum += multiplier * a[x_f];
                    }

                    graySum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, graySum);
                }
            }

            for (int x_s = 0; x_s < width; x_s++) {
                for (int y_s = 0; y_s < height; y_s++) {
                    a[y_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int y_s = 0; y_s < height; y_s++) {
                    long graySum = 0;
                    int multiplier;

                    for (int y_f = std::max(0, y_s - size_nu), loc = y_f - y_s;
                         y_f <= std::min(height - 1, y_s + size_nu); y_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        graySum += multiplier * a[y_f];
                    }

                    graySum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, graySum);
                }
            }
        }

        template<unsigned int size>
        void GaussianBlur<size>::applyTo(RGBMap &map) {
            int width = map.getWidth();
            int height = map.getHeight();
            int size_nu = size;

            RGB a[std::max(width, height)];

            for (int y_s = 0; y_s < height; y_s++) {
                for (int x_s = 0; x_s < width; x_s++) {
                    a[x_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int x_s = 0; x_s < width; x_s++) {
                    long rSum = 0, gSum = 0, bSum = 0;
                    int multiplier;

                    for (int x_f = std::max(0, x_s - size_nu), loc = x_f - x_s;
                         x_f <= std::min(width - 1, x_s + size_nu); x_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        rSum += multiplier * a[x_f].r;
                        gSum += multiplier * a[x_f].g;
                        bSum += multiplier * a[x_f].b;
                    }

                    rSum /= denominator;
                    gSum /= denominator;
                    bSum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, RGB(rSum, gSum, bSum));
                }
            }

            for (int x_s = 0; x_s < width; x_s++) {
                for (int y_s = 0; y_s < height; y_s++) {
                    a[y_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int y_s = 0; y_s < height; y_s++) {
                    long rSum = 0, gSum = 0, bSum = 0;
                    int multiplier;

                    for (int y_f = std::max(0, y_s - size_nu), loc = y_f - y_s;
                         y_f <= std::min(height - 1, y_s + size_nu); y_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        rSum += multiplier * a[y_f].r;
                        gSum += multiplier * a[y_f].g;
                        bSum += multiplier * a[y_f].b;
                    }

                    rSum /= denominator;
                    gSum /= denominator;
                    bSum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, RGB(rSum, gSum, bSum));
                }
            }
        }

        template<unsigned int size>
        void GaussianBlur<size>::applyTo(RGBAMap &map) {
            int width = map.getWidth();
            int height = map.getHeight();
            int size_nu = size;

            RGBA a[std::max(width, height)];

            for (int y_s = 0; y_s < height; y_s++) {
                for (int x_s = 0; x_s < width; x_s++) {
                    a[x_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int x_s = 0; x_s < width; x_s++) {
                    long rSum = 0, gSum = 0, bSum = 0, aSum = 0;
                    int multiplier;

                    for (int x_f = std::max(0, x_s - size_nu), loc = x_f - x_s;
                         x_f <= std::min(width - 1, x_s + size_nu); x_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        rSum += multiplier * a[x_f].r;
                        gSum += multiplier * a[x_f].g;
                        bSum += multiplier * a[x_f].b;
                        aSum += multiplier * a[x_f].a;
                    }

                    rSum /= denominator;
                    gSum /= denominator;
                    bSum /= denominator;
                    aSum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, RGBA(rSum, gSum, bSum, aSum));
                }
            }

            for (int x_s = 0; x_s < width; x_s++) {
                for (int y_s = 0; y_s < height; y_s++) {
                    a[y_s] = map.getPixelUnsafe(x_s, y_s);
                }

                for (int y_s = 0; y_s < height; y_s++) {
                    long rSum = 0, gSum = 0, bSum = 0, aSum = 0;
                    int multiplier;

                    for (int y_f = std::max(0, y_s - size_nu), loc = y_f - y_s;
                         y_f <= std::min(height - 1, y_s + size_nu); y_f++, loc++) {
                        multiplier = gaussian_gen::data[std::abs(loc)];

                        rSum += multiplier * a[y_f].r;
                        gSum += multiplier * a[y_f].g;
                        bSum += multiplier * a[y_f].b;
                        aSum += multiplier * a[y_f].a;
                    }

                    rSum /= denominator;
                    gSum /= denominator;
                    bSum /= denominator;
                    aSum /= denominator;

                    map.setPixelUnsafe(x_s, y_s, RGBA(rSum, gSum, bSum, aSum));
                }
            }
        }
    } // namespace Filters
} // namespace Sine

#endif
