//
// Created by Timothy Herchen on 2/16/18.
//

#ifndef VISUALIZATION_LINESEGMENT_H
#define VISUALIZATION_LINESEGMENT_H

#include "path.h"

namespace Sine::Math {
    struct LineSegment : Path {
        Vec2d p1;
        Vec2d p2;

        LineSegment(double x1, double y1, double x2, double y2);

        LineSegment(Vec2d _p1, Vec2d _p2 = Vec2d(0, 0));

        double length() override;

        double lengthSquared();

        double x_delta();

        double y_delta();

        Vec2d start() override;

        Vec2d end() override;

        void render(Graphics::Canvas &canvas, Graphics::Pen &pen) override;

        double slope();

        Vec2d midpoint();

        bool isVertical();

        bool isHorizontal();

        bool isDegenerate();

        BoundingBox boundingBox() override;
    };
}


#endif //VISUALIZATION_LINESEGMENT_H
