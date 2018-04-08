//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_CIRCLEOBJ_H
#define VISUALIZATION_CIRCLEOBJ_H


#include "vec2.h"
#include "cycle.h"
#include "point.h"

namespace Sine::Math {
    struct Circle : Cycle {
        double r;
        Point pos;

        Circle(double radius, Point pos = {0, 0});

        Circle(double x = 0, double y = 0, double radius = 1);

        double length() override;

        Vec2d start() override;

        Vec2d end() override;

        void draw(Graphics::Canvas &c, Graphics::Pen &pen) override;

        void fillDraw(Graphics::Canvas &c, Graphics::Pen &pen) override;

        BoundingBox boundingBox() override;

        void translateBy(const Vec2d &a) override;

        void rotateBy(GeometryUtils::radians theta, const Vec2d &center) override;

        double area() override;

        std::vector<Vec2d> sample(int count) override;
    };
}

#endif //VISUALIZATION_CIRCLEOBJ_H
