#include "graphics/imageloader.h"
#include "graphics/filters/gaussian_blur.h"
#include "graphics/canvas.h"
#include "graphics/genericgraphic.h"
#include "timer.h"

int main() {
    {
        Sine::Canvas image_temp{"/Users/timoothy/Desktop/eclipse2018/2018_01_31/IMG_0001.JPG"};
        Sine::DefaultTimer timer{"load image 0001"};

        image_temp.fill(Sine::RGBA(5, 5, 100, 5));
    }
}
