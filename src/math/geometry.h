//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_GEOMETRY_H
#define VISUALIZATION_GEOMETRY_H

#include "boundingbox.h"

namespace Sine {
    namespace Math {
        class Geometry {
        public:
            virtual BoundingBox boundingBox() = 0;

            virtual void translateBy(const Vec2d &a) = 0;

            virtual void rotateBy(GeometryUtils::radians t, const Vec2d &center = {0, 0}) = 0;

            virtual void draw(Graphics::Canvas &c, Graphics::Pen &pen) = 0;

            virtual double length() = 0;

            virtual double area() = 0;
        };
    }
}


#endif //VISUALIZATION_GEOMETRY_H
