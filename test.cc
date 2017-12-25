#include "src/graphics/bitmap.h"
#include <iostream>

int main() {
  Vis::Bitmap p{400, 500};

  for (int i = 0; i < p.getWidth(); i++) {
    p.setPixel(i, i / 2 + 1, false);
  }

  p.exportToFile("/Users/timoothy/Desktop/derp.pbm");
}
