//
// Created by Timothy Herchen on 2/24/18.
//

#include "circle.h"

namespace Sine {

    namespace Math {

        Circle::Circle(Vec2d _pos, double radius) {
            pos = _pos;
            r = std::abs(radius);
        }

        Circle::Circle(double x, double y, double radius) {
            pos = Vec2d(x, y);
            r = std::abs(radius);
        }

        double Circle::length() {
            return 2 * M_PI * r;
        }

        Vec2d Circle::start() {
            return pos + Vec2d(r, 0);
        }

        Vec2d Circle::end() {
            return pos + Vec2d(r, 0);
        }

        void Circle::render(Sine::Graphics::Canvas &canvas, Sine::Graphics::Pen &pen) {
            if (pen.width > 1) {
                canvas.drawThickCircleAliased(pos.x, pos.y, r, pen.width, pen.color);
            } else {
                canvas.drawCircle<Sine::Graphics::Alias::ALIASED>(pos.x, pos.y, r, pen.color);
            }
        }

        void Circle::fillDraw(Sine::Graphics::Canvas &canvas, Sine::Graphics::Pen &pen) {
            canvas.drawFilledCircle(pos.x, pos.y, r, pen.fillcolor);
        }

        BoundingBox Circle::boundingBox() {
            return BoundingBox(pos - Vec2d(r, r), pos + Vec2d(r, r));
        }

    }
}