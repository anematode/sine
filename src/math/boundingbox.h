//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_RECTANGLE_H
#define VISUALIZATION_RECTANGLE_H

#include "graphics/canvas.h"
#include "math/vec2.h"
#include "graphics/pen.h"

namespace Sine {
    namespace Math {
        struct BoundingBox {
            Vec2d c1;
            Vec2d c2;

        public:
            BoundingBox(Vec2d _c1, Vec2d _c2);

            BoundingBox(double x1, double y1, double x2, double y2);

            double height();

            double width();

            double area();

            double length();

            void render(Graphics::Canvas &c, Graphics::Pen &p);

            void fillDraw(Graphics::Canvas &c, Graphics::Pen &p);
        };
    }
}

#endif //VISUALIZATION_RECTANGLE_H
