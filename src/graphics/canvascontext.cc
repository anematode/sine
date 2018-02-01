//
// Created by Timothy Herchen on 1/19/18.
//

#include "canvascontext.h"

namespace Sine {
    CanvasContext::CanvasContext(Pixmap<RGB>* p) {
        canvas = p;

        width = p->getWidth();
        height = p->getHeight();
        area = p->getArea();
    }

    Pixmap<RGB>* CanvasContext::getCanvas() {
        return canvas;
    }

    inline bool CanvasContext::hasMasks() {
        return !masks.empty();
    }

    inline int CanvasContext::pairToIndex(int x, int y) {
        return canvas->pairToIndex(x, y);
    }

    inline bool CanvasContext::pixelAllowed(int i) {
        return true;
    }

    inline bool CanvasContext::pixelAllowed(int x, int y) {
        return true;
    }

}