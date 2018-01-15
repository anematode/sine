#include "src/graphics/filters/gaussian_blur.h"
#include "src/graphics/imageloader.h"
#include "src/graphics/imageconverter.h"
#include <iostream>

int main() {
  using namespace Vis;

  ImageLoader<RGBMap> image_loader;
  auto image = image_loader.load("/Users/timoothy/Desktop/4254372-grayscale-image.jpg");

  ImageConverter<RGBMap, Bitmap> converter;
  auto new_image = converter.convert(*image);

  Vis::Filters::GaussianBlur<50> blur;
  blur.applyTo(*new_image);

  new_image->exportToFile("/Users/timoothy/Desktop/s_output/out.png");
}
