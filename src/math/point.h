//
// Created by Timothy Herchen on 3/3/18.
//

#ifndef VISUALIZATION_POINT_H
#define VISUALIZATION_POINT_H

#include "cycle.h"
#include "geometryutils.h"

namespace Sine {
    namespace Math {
        struct Point : public Geometry, public Vec2d {
            Point();

            Point(const Vec2d &p);

            Point(double x, double y);

            void draw(Graphics::Canvas &c, Graphics::Pen &p) override;

            void translateBy(const Vec2d &a) override;

            void rotateBy(GeometryUtils::radians angle, const Vec2d &center) override;

            BoundingBox boundingBox() override;

            double area() override;

            double length() override;
        };
    }
}


#endif //VISUALIZATION_POINT_H
