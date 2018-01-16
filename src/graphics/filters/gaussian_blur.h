#ifndef GAUSSIAN_BLUR_DEFINED_
#define GAUSSIAN_BLUR_DEFINED_

#include "filter.h"
#include <iostream>
#include <limits>

namespace Vis {
namespace Filters {

namespace GenerateGaussian {

constexpr double pow(double x, int y) {
  return y == 0 ? 1.0 : x * pow(x, y - 1);
}

constexpr int factorial(int x) { return x == 0 ? 1 : x * factorial(x - 1); }

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

double constexpr sqrtNewtonRaphson(double x, double curr, double prev) {
  return curr == prev ? curr
                      : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
}

double constexpr c_sqrt(double x) {
  return x >= 0 && x < std::numeric_limits<double>::infinity()
             ? sqrtNewtonRaphson(x, x, 0)
             : std::numeric_limits<double>::quiet_NaN();
}

const int MULT_FACTOR_LOG2 = 13;
const int MULT_FACTOR = 2 << MULT_FACTOR_LOG2;

constexpr int getGFactor(size_t index, int stddevs100) {
  return MULT_FACTOR *
         c_exp(-((int)index * (int)index) / (stddevs100 / 100.0)) /
         c_sqrt(3.14159265358979 * stddevs100 / 100.0);
}

template <unsigned... args> struct ArrayHolder {
  static const unsigned int data[sizeof...(args)];
};

template <unsigned... args>
const unsigned int ArrayHolder<args...>::data[sizeof...(args)] = {args...};

template <size_t N, int L, template <size_t, int> class F, unsigned int... args>
struct generate_array_rec {
  typedef
      typename generate_array_rec<N - 1, L, F, F<N, L>::value, args...>::result
          result;
};

template <template <size_t, int> class F, int L, unsigned int... args>
struct generate_array_rec<0, L, F, args...> {
  typedef ArrayHolder<F<0, L>::value, args...> result;
};

template <size_t N, int L, template <size_t, int> class F>
struct generate_array {
  typedef typename generate_array_rec<N - 1, L, F>::result result;
};

template <size_t index, int stddevs100> struct MetaFunc {
  enum { value = getGFactor(index, stddevs100) };
};

constexpr unsigned long sum(const unsigned int array[], int pos_first_elem, int pos_last_elem) {
  return (pos_first_elem == pos_last_elem) ? array[pos_first_elem] : array[pos_first_elem] + sum(array, pos_first_elem + 1, pos_last_elem);
}

}; // namespace GenerateGaussian
template <unsigned int size> class GaussianBlur : public Filter {
private:
  typedef typename GenerateGaussian::generate_array<
      size + 1, 50 * size, GenerateGaussian::MetaFunc>::result gaussian_gen;
  static unsigned long denominator;

public:
  void applyTo(Bitmap &map);
  void applyTo(Graymap &map);
  void applyTo(RGBMap &map);
  void applyTo(RGBAMap &map);

  void print();
};

template <unsigned int size> void GaussianBlur<size>::print() {
  for (int i = 0; i < size; i++) {
    std::cout << gaussian_gen::data[i] << ' ';
  }
}

template <unsigned int size>
unsigned long GaussianBlur<size>::denominator = GenerateGaussian::sum(gaussian_gen::data, 1, size + 1) * 2 + gaussian_gen::data[0];

template <unsigned int size> void GaussianBlur<size>::applyTo(Bitmap &map) {
  int width = map.getWidth();
  int height = map.getHeight();
  int size_nu = size;

  bool a[std::max(width, height)];

  for (int y_s = 0; y_s < height; y_s++) {
    for (int x_s = 0; x_s < width; x_s++) {
      a[x_s] = map.getPixel(x_s, y_s);
    }

    for (int x_s = 0; x_s < width; x_s++) {
      long graySum = 0;
      int multiplier;

      for (int x_f = std::max(0, x_s - size_nu), loc = x_f - x_s;
           x_f <= std::min(width - 1, x_s + size_nu); x_f++, loc++) {
        multiplier = gaussian_gen::data[std::abs(loc)];

        graySum += a[x_f] ? 0 : 256 * multiplier;
      }

      graySum /= denominator;

      map.setPixel(x_s, y_s, (graySum < 128));
    }
  }

  for (int x_s = 0; x_s < width; x_s++) {
    for (int y_s = 0; y_s < height; y_s++) {
      a[y_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, (graySum < 128));
    }
  }
}

template <unsigned int size> void GaussianBlur<size>::applyTo(Graymap &map) {
  int width = map.getWidth();
  int height = map.getHeight();
  int size_nu = size;

  unsigned char a[std::max(width, height)];

  for (int y_s = 0; y_s < height; y_s++) {
    for (int x_s = 0; x_s < width; x_s++) {
      a[x_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, graySum);
    }
  }

  for (int x_s = 0; x_s < width; x_s++) {
    for (int y_s = 0; y_s < height; y_s++) {
      a[y_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, graySum);
    }
  }
}

template <unsigned int size> void GaussianBlur<size>::applyTo(RGBMap &map) {
  int width = map.getWidth();
  int height = map.getHeight();
  int size_nu = size;

  Vis::RGB a[std::max(width, height)];

  for (int y_s = 0; y_s < height; y_s++) {
    for (int x_s = 0; x_s < width; x_s++) {
      a[x_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, Vis::RGB(rSum, gSum, bSum));
    }
  }

  for (int x_s = 0; x_s < width; x_s++) {
    for (int y_s = 0; y_s < height; y_s++) {
      a[y_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, Vis::RGB(rSum, gSum, bSum));
    }
  }
}

template <unsigned int size> void GaussianBlur<size>::applyTo(RGBAMap &map) {
  int width = map.getWidth();
  int height = map.getHeight();
  int size_nu = size;

  Vis::RGBA a[std::max(width, height)];

  for (int y_s = 0; y_s < height; y_s++) {
    for (int x_s = 0; x_s < width; x_s++) {
      a[x_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, Vis::RGBA(rSum, gSum, bSum, aSum));
    }
  }

  for (int x_s = 0; x_s < width; x_s++) {
    for (int y_s = 0; y_s < height; y_s++) {
      a[y_s] = map.getPixel(x_s, y_s);
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

      map.setPixel(x_s, y_s, Vis::RGBA(rSum, gSum, bSum, aSum));
    }


  }
}
} // namespace Filters
} // namespace Vis

#endif
