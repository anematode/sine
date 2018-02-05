//
// Created by Timothy Herchen on 1/31/18.
//

#include "genericgraphic.h"

namespace Sine::Graphics {
    GenericGraphic::GenericGraphic(int width, int height, int _xmin, int _ymin, ColorUtils::ColorMix _mix) : Canvas(
            width, height), xmin(_xmin),
                                                                                                             ymin(_ymin),
                                                                                                             mix(_mix) {
    }

    void GenericGraphic::render(RenderingContext &p) {
        p.mixImage(*this, xmin, ymin, mix);
    }
}