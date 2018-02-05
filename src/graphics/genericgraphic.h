//
// Created by Timothy Herchen on 1/31/18.
//

#ifndef VISUALIZATION_GENERICGRAPHIC_H
#define VISUALIZATION_GENERICGRAPHIC_H

#include "graphic.h"
#include "canvas.h"
#include "renderingcontext.h"

namespace Sine::Graphics {
    /**
     * Simple Graphic that inherits from Canvas and simply mixes itself into the RenderingContext at a specified location.
     */
    class GenericGraphic : public Graphic, public Canvas {
    private:
        int xmin;
        int ymin;
    public:
        /**
         * Simple constructor.
         * @param width Width of Graphic.
         * @param height Height of Graphic.
         * @param xmin X position of top left corner.
         * @param ymin Y position of top left corner.
         */
        GenericGraphic(int width, int height, int xmin = 0, int ymin = 0);

        /**
         * Implementation of render; just mixes in the Graphic at the specified location.
         * @param ctx Context to render to.
         */
        void render(RenderingContext &ctx) override;
    };
}


#endif //VISUALIZATION_GENERICGRAPHIC_H
