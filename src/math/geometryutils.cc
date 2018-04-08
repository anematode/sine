//
// Created by Timothy Herchen on 3/3/18.
//

#include "geometryutils.h"

namespace Sine {
    namespace Math {
        namespace GeometryUtils {
            double magnitudeSquared(double x, double y) {
                return x * x + y * y;
            }

            double magnitude(double x, double y) {
                return std::sqrt(magnitudeSquared(x, y));
            }

            double magnitudeSquared(const Vec2d &v) {
                return v.distanceSquared();
            }

            double magnitude(const Vec2d &v) {
                return v.distance();
            }

            double distanceSquared(double x1, double y1, double x2, double y2) {
                return magnitudeSquared(x1 - x2, y1 - y2);
            }

            double distance(double x1, double y1, double x2, double y2) {
                return magnitude(x1 - x2, y1 - y2);
            }

            double distanceSquared(const Vec2d &v, const Vec2d &w) {
                return magnitude(v - w);
            }

            double distance(const Vec2d &v, const Vec2d &w) {
                return magnitude(v - w);
            }

            bool isVertical(const Vec2d &v, const Vec2d &w) {
                return v.x == w.x;
            }

            bool isVertical(double x1, double y1, double x2, double y2) {
                return x1 == x2;
            }

            bool isHorizontal(double x1, double y1, double x2, double y2) {
                return y1 == y2;
            }

            bool isHorizontal(const Vec2d &v, const Vec2d &w) {
                return v.y == w.y;
            }

            double angleBetween(const Vec2d &v, const Vec2d &w) {
                return std::acos((v * w) / (v.distance() * w.distance()));
            }

            double angleBetween(double x1, double y1, double x2, double y2) {
                return angleBetween({x1, y1}, {x2, y2});
            }

            Vec2d minElements(const Vec2d &v, const Vec2d &w) {
                return {std::min(v.x, w.x), std::min(v.y, w.y)};
            }

            Vec2d maxElements(const Vec2d &v, const Vec2d &w) {
                return {std::max(v.x, w.x), std::max(v.y, w.y)};
            }

            double constexpr degToRad(const double deg) {
                return deg * MathUtils::PI / 180;
            }

            double constexpr radToDeg(const double rad) {
                return rad * 180 / MathUtils::PI;
            }

            Vec2d translate(const Vec2d &c, double x, double y) {
                return {c.x + x, c.y + y};
            }

            Vec2d rotateByOrigin(const Vec2d &a, radians angle) {
                double c = std::cos(angle);
                double s = std::sin(angle);

                return {a.x * c - a.y * s, a.x * s + a.y * c};
            }

            Vec2d rotate(const Vec2d &a, radians angle, double x, double y) {
                return translate(rotateByOrigin(translate(a, -x, -y), angle), x, y);
            }

            Vec2d rotate(const Vec2d &a, radians angle, const Vec2d &v) {
                return rotate(a, angle, v.x, v.y);
            }

            bool doSegmentsIntersect(const Vec2d &p1, const Vec2d &p2, const Vec2d &p3, const Vec2d &p4) {
                return true;
            }

            bool containedInSegment(const Vec2d &a, const Vec2d &b, const Vec2d &c) {
                return true; //if ()
            }

            std::experimental::optional<Vec2d>
            segmentIntersect(const Vec2d &p1, const Vec2d &p2, const Vec2d &p3, const Vec2d &p4) {
                return Vec2d{0, 0};
            }
        }
    }

    double operator "" _rad(long double r) {
        return r;
    }

    double operator "" _deg(long double r) {
        return Math::GeometryUtils::degToRad(r);
    }

    double operator "" _rad(unsigned long long r) {
        return r;
    }

    double operator "" _deg(unsigned long long r) {
        return Math::GeometryUtils::degToRad(r);
    }
}