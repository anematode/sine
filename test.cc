#include "src/graphics/imageloader.h"
#include <iostream>

void process(Vis::Color& lum) {
  Vis::HSL lum_hsl = lum.hsl();

  if (lum_hsl.l < 160) {
    lum.setColor((Vis::RGBA) Vis::Colors::BLUE);

    return;
  } else if (lum_hsl.s > 30 && lum_hsl.s < 70 && lum_hsl.h < 35 && lum_hsl.h > 5 && lum_hsl.l > 150) {
    lum.setColor((Vis::RGBA) Vis::Colors::GREEN);

    return;
  } else {
    lum.setColor((Vis::RGBA) Vis::Colors::RED);

    return;
  }
}

const int gaussian[5][5] = {
  {1, 4, 6, 4, 1},
  {4, 16, 26, 16, 4},
  {7, 26, 41, 26, 7},
  {4, 16, 26, 16, 4},
  {1, 4, 6, 4, 1}
};

void filter(std::unique_ptr<Vis::RGBMap>& image) {
  int width = image->getWidth();
  int height = image->getHeight();

  Vis::RGBMap new_image{width, height};
  Vis::RGB temp;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Vis::RGB pixel_avg(0, 0, 0);

      for (int k = -2; k < 3; k++) {
        if (i + k >= 0 && i + k < width) {
          for (int l = -2; l < 3; l++) {
            if (j + l >= 0 && j + l < height) {
              double gfactor = gaussian[k + 2][l + 2] / 273.0;
              temp = image->getPixel(i + k, j + l);

              pixel_avg.r += temp.r * gfactor;
              pixel_avg.g += temp.g * gfactor;
              pixel_avg.b += temp.b * gfactor;
            }
          }
        }
      }

      new_image.setPixel(i, j, pixel_avg);
    }
  }

  image->copyFrom(new_image);
}

int main() {
  using namespace Vis;

  ImageLoader<RGBMap> loader;
  auto image = loader.load("/Users/timoothy/Downloads/dad_test.jpg");

  filter(image);

  for (int i = 0; i < image->getWidth(); i++) {
    for (int j = 0; j < image->getHeight(); j++) {
      Color lum = image->getPixel(i, j);

      process(lum);
      image->setPixel(i, j, lum);
    }
  }

  image->exportToFile("/Users/timoothy/Desktop/out.jpg");
}
