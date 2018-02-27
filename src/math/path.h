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
    class Path : public Geometry {
        virtual double length() = 0;

        virtual Vec2d start() = 0;

        virtual Vec2d end() = 0;

        virtual void render(Graphics::Canvas &c, Graphics::Pen &pen) = 0;
    };
}

#endif //VISUALIZATION_PATH_H
