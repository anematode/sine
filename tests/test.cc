#include "graphics/imageloader.h"
#include "graphics/filters/gaussian_blur.h"
#include "graphics/canvas.h"
#include "graphics/genericgraphic.h"
#include "timer.h"

int main() {
    using namespace Sine::Graphics;
    {
        Canvas image_temp{"/Users/timoothy/Desktop/nico_backward.jpg"};

        {
            Sine::General::DefaultTimer timer{"load image 0001"};

            image_temp.apply([](RGBA &c, int i) {
                c.r *= c.g / 50.0;
                c.g *= c.b / 30.0;
                c.b *= 10;

                c.r += (i % 255) / 39.0;
                c.g += (i % 230) / 50.0;
                c.b -= (i % 109) / 20.3;
            });

            Sine::Graphics::Filters::GaussianBlur<4> blur;

            blur.applyTo(image_temp);
        }

        image_temp.exportToFile("/Users/timoothy/Desktop/weirdo_jennifer.jpg");
    }
}
