//
// Created by Timothy Herchen on 2/16/18.
//

#ifndef VISUALIZATION_PATH_H
#define VISUALIZATION_PATH_H

#include "vec2.h"
#include "graphics/canvas.h"
#include "graphics/pen.h"
#include "geometry.h"

namespace Sine::Math {
    struct Path : public Geometry {
        virtual Vec2d start() = 0;

        virtual Vec2d end() = 0;

        virtual std::vector<Vec2d> sample(int count) = 0;
    };
}

#endif //VISUALIZATION_PATH_H
