//
// Created by Timothy Herchen on 4/7/18.
//

#include "polygon.h"

namespace Sine::Math {
    Polygon::Polygon(const std::vector<Vec2d> &pts) : points(pts) {

    }

    void Polygon::draw(Graphics::Canvas &c, Graphics::Pen &pen) {
        Vec2d prevPoint = start();
        for (const Vec2d &a : points) {
            LineSegment(a, prevPoint).draw(c, pen);
            prevPoint = a;
        }

        LineSegment(prevPoint, start()).draw(c, pen);
    }

    void Polygon::fillDraw(Graphics::Canvas &c, Graphics::Pen &pen) {

    }

}