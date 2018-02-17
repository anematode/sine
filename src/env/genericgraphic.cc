//
// Created by Timothy Herchen on 1/31/18.
//

#include "genericgraphic.h"

namespace Sine::Env {
    GenericGraphic::GenericGraphic(int width, int height, int _xmin, int _ymin) : Sine::Graphics::Canvas(width, height),
                                                                                  xmin(_xmin), ymin(_ymin) {
    }

    void GenericGraphic::render(RenderingContext &p) {
        p.mixImage<ColorUtils::ColorMix::MERGE>(*this, xmin, ymin);

        if (show_border) {
            drawLine(0, 0, width, height);
        }
    }
}