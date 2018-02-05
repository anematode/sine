//
// Created by Timothy Herchen on 1/31/18.
//

#include "genericgraphic.h"

namespace Sine::Graphics {
    GenericGraphic::GenericGraphic(int width, int height, int _xmin, int _ymin) : Canvas(
            width, height), xmin(_xmin), ymin(_ymin) {
    }

    void GenericGraphic::render(RenderingContext &p) {
        p.mixImage<ColorUtils::ColorMix::MERGE>(*this, xmin, ymin);
    }
}