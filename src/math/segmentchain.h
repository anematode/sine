//
// Created by Timothy Herchen on 3/1/18.
//

#ifndef VISUALIZATION_SEGMENTCHAIN_H
#define VISUALIZATION_SEGMENTCHAIN_H

#include <vector>
#include "linesegment.h"

namespace Sine {
    namespace Math {
        class SegmentChain : virtual public Path {
        protected:
            std::vector<Vec2d> points;
        public:
            SegmentChain();

            explicit SegmentChain(const std::vector<Vec2d> &pts);

            int count();

            Vec2d start() override;

            Vec2d end() override;

            double length() override;

            BoundingBox boundingBox() override;

            void draw(Graphics::Canvas &c, Graphics::Pen &pen) override;

            void addPoint(const Vec2d &c);

            void translateBy(const Vec2d &a) override;

            void rotateBy(GeometryUtils::radians theta, const Vec2d &a) override;

            double area() override;

            std::vector<Vec2d> sample(int count) override;
        };
    }
}


#endif //VISUALIZATION_SEGMENTCHAIN_H
