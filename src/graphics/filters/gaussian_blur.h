#ifndef GAUSSIAN_BLUR_DEFINED_
#define GAUSSIAN_BLUR_DEFINED_

#include "filter.h"
#include <limits>
#include <iostream>

namespace Vis {
  namespace Filters {

namespace GenerateGaussian {

constexpr double pow(double x, int y) {
    return y == 0 ? 1.0 : x * pow(x, y-1);
}

constexpr int factorial(int x) {
    return x == 0 ? 1 : x * factorial(x-1);
}

constexpr double c_exp(double x) {
    return (x < -8) ? 0 : ((x < 0) ? (1 / c_exp(-x)) : 1.0 + x + pow(x,2)/factorial(2) + pow(x, 3)/factorial(3)
        + pow(x, 4)/factorial(4) + pow(x, 5)/factorial(5)
        + pow(x,6)/factorial(6) + pow(x, 7)/factorial(7)
    + pow(x, 8)/factorial(8) + pow(x, 9)/factorial(9));
}

    double constexpr sqrtNewtonRaphson(double x, double curr, double prev)
    {
        return curr == prev ? curr : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
    }

double constexpr c_sqrt(double x)
{
    return x >= 0 && x < std::numeric_limits<double>::infinity() ? sqrtNewtonRaphson(x, x, 0) : std::numeric_limits<double>::quiet_NaN();
}

const int MULT_FACTOR = 2 << 25;

constexpr int getGFactor(size_t index, int stddevs100) {
  return MULT_FACTOR * c_exp(-((int)index * (int)index) / (stddevs100 / 100.0)) / c_sqrt(3.14159265358979 * stddevs100 / 100.0);
}

template<unsigned... args> struct ArrayHolder {
    static const unsigned int data[sizeof...(args)];
};

template<unsigned... args>
const unsigned int ArrayHolder<args...>::data[sizeof...(args)] = { args... };

template<size_t N, int L, template<size_t, int> class F, unsigned int... args>
struct generate_array_impl {
    typedef typename generate_array_impl<N-1, L, F, F<N, L>::value, args...>::result result;
};

template<template<size_t, int> class F, int L, unsigned int... args>
struct generate_array_impl<0, L, F, args...> {
    typedef ArrayHolder<F<0, L>::value, args...> result;
};

template<size_t N, int L, template<size_t, int> class F>
struct generate_array {
    typedef typename generate_array_impl<N-1, L, F>::result result;
};

template<size_t index, int stddevs100> struct MetaFunc {
    enum {
      value = getGFactor(index, stddevs100)
    };
};

constexpr int getGaussianSum(size_t index, int stddevs100) {
  return getGFactor(index, stddevs100) + ((index <= 0) ? 0 : getGaussianSum(index - 1, stddevs100));
}

};
    template <unsigned int size>
    class GaussianBlur : public Filter {
    private:
      typedef typename GenerateGaussian::generate_array<size, 50 * size, GenerateGaussian::MetaFunc>::result gaussian_gen;
      static int denominator;
    public:
      void applyTo(Bitmap& map);
      void applyTo(Graymap& map);
      void applyTo(RGBMap& map);
      void applyTo(RGBAMap& map);

      void print();
    };

    template <unsigned int size>
    int GaussianBlur<size>::denominator = GenerateGaussian::getGaussianSum(size, 50 * size);

    template <unsigned int size>
    void GaussianBlur<size>::print() {
      for (int i = 0; i < size; i++) {
        std::cout << gaussian_gen::data[i] << ' ';
      }
    }

    template <unsigned int size>
    void GaussianBlur<size>::applyTo(Bitmap& map) {

    }

    template <unsigned int size>
    void GaussianBlur<size>::applyTo(Graymap& map) {

    }

    template <unsigned int size>
    void GaussianBlur<size>::applyTo(RGBMap& map) {

    }

    template <unsigned int size>
    void GaussianBlur<size>::applyTo(RGBAMap& map) {

    }
  }
}


#endif
