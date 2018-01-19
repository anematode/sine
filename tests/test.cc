#include "graphics/imageloader.h"
#include "graphics/filters/gaussian_blur.h"
#include <iostream>

int main() {
    Vis::ImageLoader<Vis::RGBMap> loader;
    auto image = loader.load("/Users/timoothy/Desktop/FunThings/IMG_0480.JPG");

    Vis::Filters::GaussianBlur<20> blur;
    blur.applyTo(*image);

    image->exportToFile("/Users/timoothy/Desktop/test.png");
}
