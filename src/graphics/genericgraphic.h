//
// Created by Timothy Herchen on 1/31/18.
//

#ifndef VISUALIZATION_GENERICGRAPHIC_H
#define VISUALIZATION_GENERICGRAPHIC_H

#include "graphic.h"
#include "canvas.h"
#include "renderingcontext.h"

namespace Sine {
    class GenericGraphic : public Graphic, public Canvas {
    private:
        int xmin;
        int ymin;
    public:
        GenericGraphic(int width, int height, int xmin = 0, int ymin = 0);

        void render(RenderingContext &ctx) override;
    };
}


#endif //VISUALIZATION_GENERICGRAPHIC_H
