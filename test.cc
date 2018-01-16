#include "src/graphics/filters/gaussian_blur.h"
#include "src/graphics/imageloader.h"
#include "src/graphics/imageconverter.h"
#include "src/graphics/filters/saturate_filter.h"
#include <cstdint>
#include <iostream>

int main() {
  using namespace Vis;

  ImageLoader<RGBMap> image_loader;
  auto image = image_loader.load("/Users/timoothy/Desktop/IMG_0483.jpg");

  auto test = Vis::Filters::Desaturate(255);

  Vis::Filters::GaussianBlur<3> blur;
  blur.applyTo(*image);
  test.applyTo(*image);

  image->exportToFile("/Users/timoothy/Desktop/s_output/k.jpg");

}
