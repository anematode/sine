#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "graphics/imageloader.h"
#include "graphics/filters/gaussian_blur.h"
//#include "graphics/canvas.h"
#include <iostream>

int main() {
    Vis::ImageLoader<Vis::RGBMap> loader;
    auto image = loader.load("/Users/timoothy/Desktop/FunThings/IMG_0480.JPG").sample(0.2);

    Vis::Filters::GaussianBlur<200> blur;
    blur.applyTo(image);

    //Vis::Canvas canv(image);

    /*canv.exportToFile("/Users/timoothy/Desktop/udd.png");
    Vis::CanvasContext ctx(&canv);*/

    image.exportToFile("/Users/timoothy/Desktop/test.png");
}
