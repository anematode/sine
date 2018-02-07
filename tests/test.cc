#include "graphics/filters/gaussian_blur.h"
#include "graphics/canvas.h"

int main() {
    using namespace Sine::Graphics;
    {
        Canvas image_temp{"/Users/timoothy/Desktop/2018-02-05-1.PNG"};

        {
            Sine::Graphics::Filters::GaussianBlur<2> blur; // smooth out noise

            blur.applyTo(image_temp);

            image_temp.apply([](RGBA &c) {
                // Implode colors but deterministically
                c.r += c.g;
                c.g *= 3;
                c.b *= 4;
                c.r *= 2;
                c.b += c.r;

                c = ColorUtils::darken(c.hsl(), 75).rgba();
            });
        }

        image_temp.exportToFile("/Users/timoothy/Desktop/edmund.jpg");
    }
}
