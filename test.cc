#include "src/graphics/filters/gaussian_blur.h"
#include <iostream>

constexpr double sq(double a) {
  return a * a;
}

int main() {
  using namespace Vis::Filters::GenerateGaussian;


      const size_t count = 5;
      typedef generate_array<count, 200, MetaFunc>::result A;

      for (size_t i=0; i<count; ++i)
          std::cout << A::data[i] << "\n";
}
