#include "src/math/vec2.h"
#include <iostream>

int main() {
  Vis::Vec2f a{2, 3};

  std::complex<double> f{a};

  std::cout << f << std::endl;
}
