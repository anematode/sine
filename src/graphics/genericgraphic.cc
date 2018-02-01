//
// Created by Timothy Herchen on 1/31/18.
//

#include "genericgraphic.h"

namespace Sine {
    GenericGraphic::GenericGraphic(int width, int height, int _xmin, int _ymin) : Canvas(width, height), xmin(_xmin),
                                                                                  ymin(_ymin) {

    }

    void GenericGraphic::render(RenderingContext &p) {
        int max_i = std::min(p.getWidth(), width + xmin);
        int max_j = std::min(p.getHeight(), height + ymin);
        int sample_x = 0;

        for (int i = xmin; i < max_i; i++, sample_x++) {
            int sample_y = 0;
            for (int j = ymin; j < max_j; j++, sample_y++) {
                p.setPixel(i, j, getPixel(sample_x, sample_y, false), false);
            }
        }
    }
}