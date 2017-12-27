#include "src/graphics/rgbmap.h"
#include <iostream>

int main() {
  Vis::RGBMap p{400, 500};

  for (int i = 0; i < p.getWidth(); i++) {
    p.setPixel(i, i / 2 + 1, Vis::RGB(2, 5, 5));
  }

  p.exportToFile("/Users/timoothy/Desktop/derp.jpg");
}
