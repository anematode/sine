#ifndef FILTER_DEFINED_
#define FILTER_DEFINED_

#include "../bitmap.h"
#include "../graymap.h"
#include "../rgbamap.h"
#include "../rgbmap.h"

namespace Vis {
  class Filter {
  public:
    virtual void applyTo(Bitmap& p) = 0;
    virtual void applyTo(Graymap& p) = 0;
    virtual void applyTo(RGBMap& p) = 0;
    virtual void applyTo(RGBAMap& p) = 0;
  };
}

#endif
