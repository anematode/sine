//
// Created by Timothy Herchen on 1/26/18.
//

#include <graphics/algorithms/circle.h>
#include "canvas.h"
#include "graphics/algorithms/line.h"
#include "graphics/algorithms/bezier.h"

namespace Sine::Graphics {
    Canvas::Canvas(int width, int height) : Pixmap<RGBA>(width, height) {
        fill(RGBA(255, 255, 255, 0));
    }

    Canvas::Canvas(const std::string &filename) : Pixmap<RGBA>(
            ImageLoader<RGBAMap>::loadAny(filename)) { // Load file using ImageLoader
    }

    Canvas::Canvas(const Canvas &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        width = p.getWidth();
        height = p.getHeight();

        area = p.area;

        copyFrom(p); // Copy pixel data from p
    }

    Canvas::Canvas(const Pixmap<RGBA> &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        copyFrom(p); // Copy pixel data from p
    }

    // Use ImageConverter to convert between given Pixmaps to RGBAMap
    typedef ImageConverter<RGBAMap> RGBAMapConverter;

    Canvas::Canvas(const Pixmap<RGB> &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        copyFrom(RGBAMapConverter::convert(p));
    }

    Canvas::Canvas(const Graymap &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        copyFrom(RGBAMapConverter::convert(p));
    }

    Canvas::Canvas(const Bitmap &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        copyFrom(RGBAMapConverter::convert(p));
    }

    void Canvas::fill(Color color) {
        std::fill_n(pixels, area, color.rgba());
    }

    void Canvas::clear() {
        fill(RGBA(255, 255, 255, 0));
    }

    Canvas &Canvas::operator=(const Canvas &c) {
        if (c.getArea() != area) {
            delete[] pixels;
            pixels = new RGBA[c.getArea()];
            area = c.getArea();
        }

        for (int i = 0; i < area; i++) {
            setPixelUnsafe(i, c.getPixelUnsafe(i));
        }

        width = c.getWidth();
        height = c.getHeight();

        return *this;
    };

    /**
     * Use Pixmap<RGBA> assignment, copy, move operators
     */
    Canvas &Canvas::operator=(Canvas &&c) noexcept {
        delete[] pixels;

        pixels = c.pixels;
        c.pixels = nullptr;

        width = c.getWidth();
        height = c.getHeight();

        return *this;
    };

    void Canvas::drawLineAliased(float x1, float y1, float x2, float y2, const RGBA &color) {
        Algorithms::drawMaskedBresenham(x1, y1, x2, y2, 0, 0, width, height, [&](int x, int y) {
            mergePixel(x, y, color);
        });
    }

    void Canvas::drawLineAntialiased(float x1, float y1, float x2, float y2, const RGBA &color) {
        Algorithms::drawMaskedXiaolin(x1, y1, x2, y2, -1, -1, width + 1, height + 1, [&](int x, int y, uint8_t c) {
            mergePixelNoThrow(x, y, RGBA(color.r, color.g, color.b, 255 - c));
        });
    }

    void Canvas::drawThickLineAliased(float x1, float y1, float x2, float y2, float thickness, const RGBA &color) {
        Algorithms::drawMaskedBresenhamThick(x1, y1, x2, y2, thickness, 0, 0, width, height, [&](int x, int y) {
            mergePixel(x, y, color);
        });
    }

    void Canvas::drawThickLineAntialiased(float x1, float y1, float x2, float y2, float thickness, const RGBA &color) {
        Algorithms::drawMaskedXiaolinThick(x1, y1, x2, y2, thickness, 0, 0, width, height,
                                           [&](int x, int y, uint8_t c) {

                                               mergePixel(x, y, RGBA(color.r, color.g, color.b, 255 - c));
                                           });
    }

    void
    Canvas::drawQuadraticBezierAliased(float x1, float y1, float x2, float y2, float x3, float y3, const RGBA &color) {
        Algorithms::drawQuadraticBezier(x1, y1, x2, y2, x3, y3, [&](int x, int y) {
            mergePixel(x, y, color);
        });
    }

    void Canvas::drawQuadraticBezierAntialiased(float x1, float y1, float x2, float y2, float x3, float y3,
                                                const RGBA &color) {
        Algorithms::drawQuadraticBezierAntialiased(x1, y1, x2, y2, x3, y3, [&](int x, int y, uint8_t c) {
            mergePixel(x, y, RGBA(color.r, color.g, color.b, 255 - c));
        });
    }

    void Canvas::drawCircleAliased(float x1, float y1, int r, const RGBA &color) {
        Algorithms::drawCircle(x1, y1, r, [&](int x, int y) {
            mergePixel(x, y, color);
        });
    }

    void Canvas::drawCircleAntialiased(float x1, float y1, float r, const RGBA &color) {
        Algorithms::drawCircleAntialiased(x1, y1, r, [&](int x, int y, uint8_t c) {
            mergePixel(x, y, RGBA(color.r, color.g, color.b, 255 - c));
        });
    }
}
