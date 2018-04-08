//
// Created by Timothy Herchen on 2/24/18.
//

#include "boundingbox.h"
#include "linesegment.h"

namespace Sine {
    namespace Math {
        BoundingBox::BoundingBox(Vec2d _c1, Vec2d _c2) {
            c1 = Vec2d(std::min(_c1.x, _c2.x), std::min(_c1.y, _c2.y));
            c2 = Vec2d(std::max(_c1.x, _c2.x), std::max(_c1.y, _c2.y));
        }

        BoundingBox::BoundingBox(double x1, double y1, double x2, double y2) {
            c1 = Vec2d(std::min(x1, x2), std::min(y1, y2));
            c2 = Vec2d(std::max(x1, x2), std::max(y1, y2));
        }

        double BoundingBox::height() {
            return c2.y - c1.y;
        }

        double BoundingBox::width() {
            return c2.x - c1.x;
        }

        double BoundingBox::area() {
            return height() * width();
        }

        double BoundingBox::length() {
            return 2 * height() + 2 * width();
        }

        bool BoundingBox::isDegenerate() {
            return (height() == 0 && width() == 0);
        }

        void BoundingBox::render(Graphics::Canvas &c, Graphics::Pen &p) {
            Math::LineSegment(c1, Vec2d(c1.x, c2.y)).draw(c, p);
            Math::LineSegment(Vec2d(c1.x, c2.y), c2).draw(c, p);
            Math::LineSegment(c2, Vec2d(c2.x, c1.y)).draw(c, p);
            Math::LineSegment(Vec2d(c2.x, c1.y), c1).draw(c, p);
        }

        void BoundingBox::fillDraw(Graphics::Canvas &c, Graphics::Pen &p) {
            c.fillRect(std::round(c1.x), std::round(c1.y), std::round(c2.x), std::round(c2.y), p.fillcolor);
        }

        BoundingBox unionize(const BoundingBox &c, const BoundingBox &d) {
            return {GeometryUtils::minElements(c.c1, d.c1), GeometryUtils::maxElements(c.c2, d.c2)};
        }

        BoundingBox intersect(const BoundingBox &c, const BoundingBox &d) {
            auto leftCorner = GeometryUtils::maxElements(c.c1, d.c1);
            auto rightCorner = GeometryUtils::minElements(c.c2, d.c2);

            if (leftCorner.x > rightCorner.x || leftCorner.y > rightCorner.y) {
                return {0, 0, 0, 0};
            }

            return {leftCorner, rightCorner};
        }
    }
}
