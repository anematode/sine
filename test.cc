#include "src/graphics/canvas.h"
#include "src/graphics/imageloader.h"
#include "src/graphics/filters/light_filter.h"
#include "src/graphics/filters/gaussian_blur.h"
#include <cstdint>
#include <iostream>

int main() {
  using namespace Vis;

  ImageLoader<RGBMap> image_loader;
  auto image = image_loader.load("/Users/timoothy/Desktop/4254372-grayscale-image.jpg");

  Canvas<RGB> p = Canvas<RGB>(*image);

  /*Vis::Filters::Lighten lit_filter(50);

  Vis::Filters::GaussianBlur<100> blur;
  blur.applyTo(*image);
  lit_filter.applyTo(*image);*/

  p.exportToFile("/Users/timoothy/Desktop/s_output/k.jpg");
}
