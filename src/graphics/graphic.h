//
// Created by Timothy Herchen on 1/29/18.
//

#ifndef VISUALIZATION_GRAPHIC_H
#define VISUALIZATION_GRAPHIC_H

namespace Sine::Graphics {
    class RenderingContext;

    /**
     * Abstract class which all Graphics inherit from.
     */
    class Graphic {
    public:
        /**
         * Renders a graphic, given a context to render it in.
         * @param ctx Context to render to.
         */
        virtual void render(RenderingContext &ctx) = 0;
    };
}


#endif //VISUALIZATION_GRAPHIC_H
