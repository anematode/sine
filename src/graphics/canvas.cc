//
// Created by Timothy Herchen on 1/26/18.
//

#include <graphics/algorithms/circle.h>
#include <graphics/algorithms/thickener.h>
#include "canvas.h"
#include "graphics/algorithms/line.h"
#include "graphics/algorithms/bezier.h"
#include "filters/gaussian_blur.h"

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
            mergePixelNoThrow(x, y, color);
        });
    }

    void Canvas::drawLineAntialiased(float x1, float y1, float x2, float y2, const RGBA &color) {
        Algorithms::drawMaskedXiaolin(x1, y1, x2, y2, -1, -1, width + 1, height + 1, [&](int x, int y, uint8_t c) {
            mergePixelNoThrow(x, y, RGBA(color.r, color.g, color.b, 255 - c));
        });
    }

    void Canvas::drawThickLineAliased(float x1, float y1, float x2, float y2, float thickness, const RGBA &color) {
        Algorithms::drawMaskedBresenhamThick(x1, y1, x2, y2, thickness, 0, 0, width, height, [&](int x, int y) {
            mergePixelNoThrow(x, y, color);
        });
    }

    void Canvas::drawThickLineAntialiased(float x1, float y1, float x2, float y2, float thickness, const RGBA &color) {
        Algorithms::drawMaskedXiaolinThick(x1, y1, x2, y2, thickness, 0, 0, width, height,
                                           [&](int x, int y, uint8_t c) {
                                               mergePixelNoThrow(x, y, RGBA(color.r, color.g, color.b, 255 - c));
                                           });
    }

    void
    Canvas::drawQuadraticBezierAliased(float x1, float y1, float x2, float y2, float x3, float y3, const RGBA &color) {
        Algorithms::drawQuadraticBezier(x1, y1, x2, y2, x3, y3, [&](int x, int y) {
            mergePixelNoThrow(x, y, color);
        });
    }

    void Canvas::drawQuadraticBezierAntialiased(float x1, float y1, float x2, float y2, float x3, float y3,
                                                const RGBA &color) {
        Algorithms::drawQuadraticBezierAntialiased(x1, y1, x2, y2, x3, y3, [&](int x, int y, uint8_t c) {
            mergePixelNoThrow(x, y, RGBA(color.r, color.g, color.b, 255 - c));
        });
    }

    void Canvas::drawCircleAliased(float x1, float y1, int r, const RGBA &color) {
        Algorithms::drawCircle(x1, y1, r, [&](int x, int y) {
            mergePixelNoThrow(x, y, color);
        });
    }

    void Canvas::drawCircleAntialiased(float x1, float y1, float r, const RGBA &color) {
        Algorithms::drawCircleAntialiased(x1, y1, r, [&](int x, int y, uint8_t c) {
            mergePixelNoThrow(x, y, RGBA(color.r, color.g, color.b, 255 - c));
        });
    }

    void Canvas::drawFilledCircle(float x1, float y1, int r, const RGBA &color) {
        Algorithms::drawFilledCircle(x1, y1, r, [&](int x, int y) {
            mergePixelNoThrow(x, y, color);
        });
    }

    void Canvas::drawThickCircleAliased(float x1, float y1, int r, float thickness, const RGBA &color) {
        Algorithms::drawCircle(x1, y1, r, Algorithms::thickenForwardAliasedDraw([&](int x, int y) {
            mergePixelNoThrow(x, y, color);
        }, thickness));
    }

    void Canvas::fillRect(int x1, int y1, int x2, int y2, const RGBA &color) {
        for (int i = std::max(std::min(x1, x2), 0); i < std::min(std::max(x1, x2), width); i++) {
            for (int j = std::max(std::min(y1, y2), 0); j < std::min(std::max(y1, y2), height); j++) {
                mergePixelNoThrow(i, j, color);
            }
        }
    }

    bool isInteger(float f) {
        return f == std::ceil(f);
    }

    float getEnd(float f) {
        return f - std::trunc(f);
    }

    Canvas Canvas::smooth_sample(double b) {
        int newWidth = width * b;
        int newHeight = height * b;

        Canvas ret{newWidth, newHeight};

        if (newWidth == width && newHeight == height) {
            ret.copyFrom(*this);
            return ret;
        }

        for (int i = 0; i < newWidth; i++) {
            for (int j = 0; j < newHeight; j++) {
                float start_x = i / b;
                float start_y = j / b;
                float end_x = (i + 1) / b;
                float end_y = (j + 1) / b;

                double r = 0, g = 0, b = 0, a = 0;
                double pixelCount = 0;

                RGBA c;

                for (int x = std::ceil(start_x); x < std::floor(end_x); x++) {
                    for (int y = std::ceil(start_y); y < std::floor(end_y); y++) {
                        c = getPixelUnsafe(x, y);

                        r += c.r;
                        g += c.g;
                        b += c.b;
                        a += c.a;

                        pixelCount += 1;
                    }
                }

                if (!isInteger(start_x)) { // Count left side
                    float x_f = 1 - getEnd(start_x);
                    int start_x_floor = std::floor(start_x);

                    if (!isInteger(start_y)) { // Count top left corner
                        c = getPixelUnsafe(start_x_floor, std::floor(start_y));
                        float x_y_f = x_f * (1 - getEnd(start_y));

                        r += x_y_f * c.r;
                        g += x_y_f * c.g;
                        b += x_y_f * c.b;
                        a += x_y_f * c.a;

                        pixelCount += x_y_f;
                    }

                    for (int y_d = std::ceil(start_y); y_d < std::floor(end_y); y_d++) {
                        c = getPixelUnsafe(start_x_floor, y_d);

                        r += x_f * c.r;
                        g += x_f * c.g;
                        b += x_f * c.b;
                        a += x_f * c.a;

                        pixelCount += x_f;
                    }
                }

                if (!isInteger(end_x)) { // Count right side
                    float x_f = getEnd(end_x);
                    int end_x_ceil = std::ceil(end_x);

                    if (!isInteger(end_y)) { // Count bottom right corner
                        c = getPixelUnsafe(end_x_ceil, std::ceil(end_y));
                        float x_y_f = x_f * getEnd(end_y);

                        r += x_y_f * c.r;
                        g += x_y_f * c.g;
                        b += x_y_f * c.b;
                        a += x_y_f * c.a;

                        pixelCount += x_y_f;
                    }

                    for (int y_d = std::ceil(start_y); y_d < std::floor(end_y); y_d++) {
                        c = getPixelUnsafe(end_x_ceil, y_d);

                        r += x_f * c.r;
                        g += x_f * c.g;
                        b += x_f * c.b;
                        a += x_f * c.a;

                        pixelCount += x_f;
                    }
                }

                if (!isInteger(start_y)) { // Count top side
                    float y_f = 1 - getEnd(start_y);
                    int start_y_floor = std::floor(start_y);

                    if (!isInteger(end_x)) { // Count top right corner
                        c = getPixelUnsafe(std::ceil(end_x), start_y_floor);
                        float x_y_f = y_f * getEnd(end_x);

                        r += x_y_f * c.r;
                        g += x_y_f * c.g;
                        b += x_y_f * c.b;
                        a += x_y_f * c.a;

                        pixelCount += x_y_f;
                    }

                    for (int x_d = std::ceil(start_x); x_d < std::floor(end_x); x_d++) {
                        c = getPixelUnsafe(x_d, start_y_floor);

                        r += y_f * c.r;
                        g += y_f * c.g;
                        b += y_f * c.b;
                        a += y_f * c.a;

                        pixelCount += y_f;
                    }
                }

                if (!isInteger(end_y)) { // Count bottom side
                    float y_f = getEnd(end_y);
                    int end_y_ceil = std::ceil(end_y);

                    if (!isInteger(start_x)) { // Count bottom left corner
                        c = getPixelUnsafe(std::floor(start_x), end_y_ceil);
                        float x_y_f = y_f * getEnd(end_y);

                        r += x_y_f * c.r;
                        g += x_y_f * c.g;
                        b += x_y_f * c.b;
                        a += x_y_f * c.a;

                        pixelCount += x_y_f;
                    }

                    for (int x_d = std::ceil(start_x); x_d < std::floor(end_x); x_d++) {
                        c = getPixelUnsafe(x_d, end_y_ceil);

                        r += y_f * c.r;
                        g += y_f * c.g;
                        b += y_f * c.b;
                        a += y_f * c.a;

                        pixelCount += y_f;
                    }
                }

                ret.setPixelUnsafe(i, j, RGBA(r / pixelCount, g / pixelCount, b / pixelCount, a / pixelCount));
            }
        }

        return ret;
    }

    Canvas Canvas::spatialAntialias() {
        throw "no";

        Filters::GaussianBlur<2> blur;
        blur.applyTo(*this);

        auto k = sample(0.5);

        width /= 2;
        height /= 2;
        area /= 4;

        copyFrom(k);
    }

    void Canvas::fuzz() {
        Filters::GaussianBlur<1> blur;
        blur.applyTo(*this);
    }
}
