//
// Created by Timothy Herchen on 1/29/18.
//

#ifndef VISUALIZATION_GRAPHIC_H
#define VISUALIZATION_GRAPHIC_H

namespace Sine {
    class RenderingContext;

    class Graphic {
    public:
        virtual void render(RenderingContext &ctx) = 0;
    };
}


#endif //VISUALIZATION_GRAPHIC_H
