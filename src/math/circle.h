//
// Created by Timothy Herchen on 2/24/18.
//

#ifndef VISUALIZATION_CIRCLEOBJ_H
#define VISUALIZATION_CIRCLEOBJ_H


#include "vec2.h"
#include "cycle.h"

namespace Sine::Math {
    struct Circle : Cycle {
        double r;
        Vec2d pos;

        Circle(Vec2d _pos, double radius = 1);

        Circle(double x = 0, double y = 0, double radius = 1);

        double length() override;

        Vec2d start() override;

        Vec2d end() override;

        void render(Graphics::Canvas &c, Graphics::Pen &pen) override;

        void fillDraw(Graphics::Canvas &c, Graphics::Pen &pen) override;

        BoundingBox boundingBox() override;
    };
}

#endif //VISUALIZATION_CIRCLEOBJ_H
