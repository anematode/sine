//
// Created by Timothy Herchen on 3/3/18.
//

#include "point.h"

namespace Sine {
    namespace Math {
        Point::Point() {
            x = 0;
            y = 0;
        }

        Point::Point(const Vec2d &p) {
            x = p.x;
            y = p.y;
        }

        Point::Point(double _x, double _y) {
            x = _x;
            y = _y;
        }

        void Point::draw(Graphics::Canvas &c, Graphics::Pen &p) {
            c.drawFilledCircle(x, y, p.width, p.fillcolor);
        }

        BoundingBox Point::boundingBox() {
            return {x, y, x, y};
        }

        void Point::translateBy(const Vec2d &a) {
            operator+=(a);
        }

        void Point::rotateBy(GeometryUtils::radians angle, const Vec2d &center) {
            *this = GeometryUtils::rotate(*this, angle, center);
        }

        double Point::area() {
            return 0;
        }

        double Point::length() {
            return 0;
        }
    }
}