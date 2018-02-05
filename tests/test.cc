#include "graphics/imageloader.h"
#include "graphics/filters/gaussian_blur.h"
#include "graphics/canvas.h"
#include "graphics/genericgraphic.h"
#include "timer.h"

int main() {
    using namespace Sine::Graphics;
    {
        Canvas image_temp{"/Users/timoothy/Desktop/udd.png"};
        Sine::General::DefaultTimer timer{"load image 0001"};

        /*auto c = [](Sine::RGBA &c) {
            uint8_t lum = Sine::ColorUtils::getLuminance(c);
            c = Sine::RGBA(lum, lum, lum, c.a);
        };

        image_temp.apply(c);*/

        Filters::GaussianBlur<400> blur;

        blur.applyTo(image_temp);

        //std::cout << get_functor_traits<decltype(c)>::arg_count << std::endl;

        image_temp.exportToFile("/Users/timoothy/Desktop/udder.png");
    }
}
