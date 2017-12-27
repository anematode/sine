#ifndef COLOR_DEFINED_
#define COLOR_DEFINED_

#include <cmath>

namespace Vis {

typedef unsigned char color_base;

struct HSL {
  color_base h;
  color_base s;
  color_base l;
};

struct RGB {
  color_base r;
  color_base g;
  color_base b;

  RGB() {

  }

  RGB(color_base a, color_base b, color_base c) {
    r = a;
    g = b;
    b = c;
  }

  HSL hsl() {
    color_base minColor = std::fmin(r, std::fmin(g, b));
    color_base maxColor = std::fmax(r, std::fmax(g, b));

    (minColor + maxColor) / 2;
  }

  double luminance() {
    double r1 = r / 255.0;
    double g1 = g / 255.0;
    double b1 = b / 255.0;

    double minColor = std::fmin(r1, std::fmin(g1, b1));
    double maxColor = std::fmax(r1, std::fmax(g1, b1));

    return (minColor + maxColor) / 2;
  }

  double hue() {

  }
};

struct RGBA {
  color_base r;
  color_base g;
  color_base b;
  color_base a;

  RGBA() {

  }

  RGBA(color_base aR, color_base b, color_base c, color_base d) {
    r = aR;
    g = b;
    b = c;
    a = d;
  }
};

}

#endif
