//
// Created by Timothy Herchen on 3/3/18.
//

#ifndef VISUALIZATION_GEOMETRYUTILS_H
#define VISUALIZATION_GEOMETRYUTILS_H

#include "vec2.h"
#include "mathutils.h"
#include <experimental/optional>

namespace Sine {
    double operator "" _rad(long double r);

    double operator "" _deg(long double d);

    double operator "" _rad(unsigned long long r);

    double operator "" _deg(unsigned long long d);

    namespace Math {
        namespace GeometryUtils {
            using radians = double;
            using degrees = double;

            double magnitudeSquared(double x, double y);

            double magnitude(double x, double y);

            double magnitudeSquared(const Vec2d &v);

            double magnitude(const Vec2d &v);

            double distanceSquared(double x1, double y1, double x2, double y2);

            double distance(double x1, double y1, double x2, double y2);

            double distanceSquared(const Vec2d &v, const Vec2d &w);

            double distance(const Vec2d &v, const Vec2d &w);

            bool isVertical(double x1, double y1, double x2, double y2);

            bool isVertical(const Vec2d &v, const Vec2d &w);

            bool isHorizontal(double x1, double y1, double x2, double y2);

            bool isHorizontal(const Vec2d &v, const Vec2d &w);

            double angleBetween(const Vec2d &v, const Vec2d &w);

            double angleBetween(double x1, double y1, double x2, double y2);

            double constexpr degToRad(const degrees deg);

            double constexpr radToDeg(const radians rad);

            Vec2d minElements(const Vec2d &v, const Vec2d &w);

            Vec2d maxElements(const Vec2d &v, const Vec2d &w);

            Vec2d translate(const Vec2d &c, double x, double y);

            Vec2d rotateByOrigin(const Vec2d &a, radians angle);

            Vec2d rotate(const Vec2d &a, radians angle, double x, double y);

            Vec2d rotate(const Vec2d &a, radians angle, const Vec2d &center);

            bool doSegmentsIntersect(const Vec2d &p1, const Vec2d &p2, const Vec2d &p3, const Vec2d &p4);

            std::experimental::optional<Vec2d>
            segmentIntersect(const Vec2d &p1, const Vec2d &p2, const Vec2d &p3, const Vec2d &p4);

        }
    }
}


#endif //VISUALIZATION_GEOMETRYUTILS_H
