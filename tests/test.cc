#include "graphics/filters/gaussian_blur.h"
#include "graphics/canvas.h"
#include "graphics/algorithms/line.h"
#include "timer.h"

int main() {
    using namespace Sine::Graphics;

    {
        const int width = 3200;
        const int height = 3200;

        Canvas image_temp{width, height};

        {
            image_temp.fill(RGBA(0, 0, 0, 255));

            Sine::General::DefaultTimer timer{"bresenham-perf"};

            for (int i = 0; i < 1000; i++) {
                Algorithms::drawMaskedBresenham(width / 2 + 1000 * std::sin(i), height / 2 + 1000 * std::cos(i),
                                                width / 2, height / 2, 1900, 1900, width, height,
                                                [&](int x, int y) {
                                                    image_temp.setPixelNoThrow(x, y, RGBA(255, 255, 255, 255));
                                                });
            }
        }


        image_temp.exportToFile("/Users/timoothy/Desktop/edmund.png");
    }
}
