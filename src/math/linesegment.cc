//
// Created by Timothy Herchen on 2/16/18.
//

#include <vector>
#include "linesegment.h"

namespace Sine::Math {
    LineSegment::LineSegment(Vec2d _p1, Vec2d _p2) : p1(_p1), p2(_p2) {

    }

    LineSegment::LineSegment(double x1, double y1, double x2, double y2) {
        p1 = Vec2d(x1, y1);
        p2 = Vec2d(x2, y2);
    }

    double LineSegment::length() {
        return GeometryUtils::distance(p1, p2);
    }

    double LineSegment::lengthSquared() {
        return GeometryUtils::distanceSquared(p1, p2);
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

    void LineSegment::draw(Graphics::Canvas &canvas, Graphics::Pen &pen) {
        if (pen.width > 1) {
            canvas.drawThickLine<Graphics::Alias::ALIASED>(p1.x, p1.y, p2.x, p2.y, pen.width, pen.color);
        } else {
            canvas.drawLine<Graphics::Alias::ALIASED>(p1.x, p1.y, p2.x, p2.y, pen.color);
        }
    }

    BoundingBox LineSegment::boundingBox() {
        return {p1, p2};
    }

    void LineSegment::translateBy(const Vec2d &a) {
        p1 += a;
    }

    void LineSegment::rotateBy(GeometryUtils::radians theta, const Vec2d &center) {
        p1 = GeometryUtils::rotate(p1, theta, center);
        p2 = GeometryUtils::rotate(p2, theta, center);
    }

    double LineSegment::area() {
        return 0;
    }

    std::vector<Vec2d> LineSegment::sample(int count) {
        std::vector<Vec2d> out;

        double delta_x = p1.x - p2.x;
        double delta_y = p1.y - p2.y;

        out.push_back(p1);
        for (int i = 1; i < count; i++) {
            double c_f = i / (count - 1);
            out.emplace_back(p1.x + delta_x * c_f, p1.y + delta_y * c_f);
        }

        return out;
    }
}