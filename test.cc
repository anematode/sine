#include "src/graphics/filters/gaussian_blur.h"
#include "src/graphics/imageloader.h"
#include "src/graphics/imageconverter.h"
#include "src/graphics/filters/pixel_filter.h"
#include <cstdint>
#include <iostream>

void filter_f(uint8_t& y) {
  y /= 2;
}

int main() {
  using namespace Vis;

  ImageLoader<RGBMap> image_loader;
  auto image = image_loader.load("/Users/timoothy/Desktop/4254372-grayscale-image.jpg");

  auto test = Vis::Filters::makePixelFilter(filter_f);
  auto new_image = Vis::ImageConverter<Graymap>::convert(*image);


  Vis::Filters::GaussianBlur<5> blur;
  blur.applyTo(*new_image);

  test.applyTo(*new_image);
  new_image->exportToFile("/Users/timoothy/Desktop/s_output/k.jpg");

}
