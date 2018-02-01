//
// Created by Timothy Herchen on 1/19/18.
//

#ifndef VISUALIZATION_CANVASCONTEXT_H
#define VISUALIZATION_CANVASCONTEXT_H

#include "mask.h"
#include "pixmap.h"
#include <vector>

namespace Sine {

    enum class MaskChaining {
        Union,
        Intersection,
        AntiUnion,
        AntiIntersection
    };

    class CanvasContext {
    private:
        Pixmap<RGB>* canvas;

        int width;
        int height;
        size_t area;

    public:
        std::vector<Mask<RGB>> masks;
        MaskChaining maskMode = MaskChaining::Union;

        CanvasContext(Pixmap<RGB>* p);

        Pixmap<RGB>* getCanvas();

        bool hasMasks();

        int pairToIndex(int x, int y);

        bool pixelAllowed(int i);

        bool pixelAllowed(int x, int y);



    };
}

#endif //VISUALIZATION_CANVASCONTEXT_H
