#include "graphics/canvas.h"
#include "timer.h"
#include "print.h"
#include "math/circle.h"
#include "math/linesegment.h"
#include "graphics/algorithms/circle.h"


int main() {
    using namespace Sine;

    Math::Circle k{100, 100, 50};
    Graphics::Canvas g{500, 500};

    k.render(g, Graphics::BlackPen);
    auto l = k.boundingBox();
    l.render(g, Graphics::BlackPen);

    g.exportToFile("/Users/timoothy/Desktop/udd.jpg");
}
