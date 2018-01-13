#include "gaussian_blur.h"
#include <cmath>
#include <tuple>

namespace Vis {
  namespace Filters {
    int _createGaussianArray(unsigned int size)[] {
      int g_array[2 * size + 1];
      const float stddevs2 = size / 2.5;

      for (int i = -size; i <= size; i++) {
        g_array[i + size] = std::exp(-(i * i) / (2 * stddevs2)) / std::sqrt(6.28318530718 * stddevs2);
      }

      return g_array;
    }

    int _getGaussianDenominator(unsigned int size) {
      double sum = 0;
      const float stddevs2 = size / 2.5;

      for (int i = -size; i <= size; i++) {
        sum += std::exp(-(i * i) / (2 * stddevs2)) / std::sqrt(6.28318530718 * stddevs2);
      }

      return sum;
    }

    template <unsigned int size>
    int GaussianBlur<size>::gaussian_array[2 * size + 1] = _createGaussianArray(size);

    template <unsigned int size>
    int GaussianBlur<size>::denominator = _getGaussianDenominator(size);

    template <unsigned int size>
    void GaussianBlur<size>::print() {
      for (int i = 0; i < 2 * size + 1; i++) {
        std::cout << gaussian_array[i] << ' ';
      }
    }
  }
}
