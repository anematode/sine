
#include "graphics/canvas.h"
#include "graphics/filters/gaussian_blur.h"
#include "timer.h"
#include "print.h"
#include "graphics/algorithms/line.h"

double f(double x) {
    return 500 * std::cos(x / 40.0);
}

int main() {
    using namespace Sine;

    const int width = 5000;
    const int height = 5000;

    Graphics::Canvas g{width, height};
    g.apply([&](Graphics::RGBA &c) {
        c.a = 255;
    });

    {
        General::DefaultTimer d;

        g.drawQuadraticBezier<Graphics::Alias::ALIASED>(100, 100, width / 2, height / 2, 1200, 4000,
                                                        Graphics::Colors::RED);
    }

    /*Graphics::Filters::GaussianBlur<2> blur;
    blur.applyTo(g);

    g.sample(1 / 3.0)*/

    g.exportToFile("/Users/timoothy/Desktop/ass.jpg");
}
