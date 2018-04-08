//
// Created by Timothy Herchen on 2/24/18.
//

#include <vector>
#include "circle.h"

namespace Sine {

    namespace Math {
        Circle::Circle(double radius, Point _pos) {
            pos = _pos;
            r = std::abs(radius);
        }

        Circle::Circle(double x, double y, double radius) {
            pos = Vec2d(x, y);
            r = std::abs(radius);
        }

        double Circle::length() {
            return 2 * M_PI * r;
        }

        Vec2d Circle::start() {
            return pos + Vec2d(r, 0);
        }

        Vec2d Circle::end() {
            return pos + Vec2d(r, 0);
        }

        void Circle::draw(Sine::Graphics::Canvas &canvas, Sine::Graphics::Pen &pen) {
            if (pen.width > 1) {
                canvas.drawThickCircleAliased(pos.x, pos.y, r, pen.width, pen.color);
            } else {
                canvas.drawCircle<Sine::Graphics::Alias::ALIASED>(pos.x, pos.y, r, pen.color);
            }
        }

        void Circle::fillDraw(Sine::Graphics::Canvas &canvas, Sine::Graphics::Pen &pen) {
            canvas.drawFilledCircle(pos.x, pos.y, r, pen.fillcolor);
        }

        BoundingBox Circle::boundingBox() {
            return BoundingBox(pos - Vec2d(r, r), pos + Vec2d(r, r));
        }

        void Circle::rotateBy(GeometryUtils::radians theta, const Vec2d &center) {
            pos = GeometryUtils::rotate(pos, theta, center);
        }

        void Circle::translateBy(const Vec2d &a) {
            pos += a;
        }

        double Circle::area() {
            return M_PI * r * r;
        }

        std::vector<Vec2d> Circle::sample(int count) {
            if (count < 1) throw std::invalid_argument("At least one point must be sampled.");

            std::vector<Vec2d> out;

            double angle = 0;
            double angle_d = 2 * M_PI / count;

            for (int i = 0; i < count; i++) {
                out.emplace_back(r * std::cos(angle) + pos.x, r * std::sin(angle) + pos.y);
                angle += angle_d;
            }

            return out;
        }

    }
}