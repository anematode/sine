//
// Created by Timothy Herchen on 2/16/18.
//

#include "linesegment.h"

namespace Sine::Math {
    LineSegment::LineSegment(Vec2d _p1, Vec2d _p2) : p1(_p1), p2(_p2) {

    }

    LineSegment::LineSegment(double x1, double y1, double x2, double y2) {
        p1 = Vec2d(x1, y1);
        p2 = Vec2d(x2, y2);
    }

    double LineSegment::length() {
        double x_d = x_delta();
        double y_d = y_delta();

        return std::sqrt(x_d * x_d + y_d * y_d);
    }

    double LineSegment::lengthSquared() {
        double x_d = x_delta();
        double y_d = y_delta();

        return x_d * x_d + y_d * y_d;
    }

    double LineSegment::x_delta() {
        return p2.x - p1.x;
    }

    double LineSegment::y_delta() {
        return p2.y - p1.y;
    }

    double LineSegment::slope() {
        return y_delta() / x_delta();
    }

    Vec2d LineSegment::midpoint() {
        return Vec2d((p1.x + p2.x) / 2, (p2.y + p2.y) / 2);
    }

    bool LineSegment::isHorizontal() {
        return (p1.y == p2.y);
    }

    bool LineSegment::isVertical() {
        return (p1.x == p2.x);
    }

    bool LineSegment::isDegenerate() {
        return isHorizontal() && isVertical();
    }

    Vec2d LineSegment::start() {
        return p1;
    }

    Vec2d LineSegment::end() {
        return p2;
    }

    void LineSegment::render(Graphics::Canvas &canvas, Graphics::Pen &pen) {
        if (pen.width > 1) {
            canvas.drawThickLine<Graphics::Alias::ALIASED>(p1.x, p1.y, p2.x, p2.y, pen.width, pen.color);
        } else {
            canvas.drawLine<Graphics::Alias::ALIASED>(p1.x, p1.y, p2.x, p2.y, pen.color);
        }
    }

    BoundingBox LineSegment::boundingBox() {
        return {p1, p2};
    }
}