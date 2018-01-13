#ifndef GAUSSIAN_BLUR_DEFINED_
#define GAUSSIAN_BLUR_DEFINED_

#include "filter.h"
#include <iostream>

namespace Vis {
  namespace Filters {
    template <unsigned int size>
    class GaussianBlur : public Filter {
      static int gaussian_array[2 * size + 1];
      static int denominator;

      void applyTo(Bitmap& map);
      void applyTo(Graymap& map);
      void applyTo(RGBMap& map);
      void applyTo(RGBAMap& map);

      void print();
    };
  }
}


#endif
