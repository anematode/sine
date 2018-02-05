//
// Created by Timothy Herchen on 1/26/18.
//

#include "canvas.h"

namespace Sine::Graphics {
    Canvas::Canvas(int width, int height) : Pixmap<RGBA>(width, height) {

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

    void Canvas::pasteImage(Bitmap &image, int x, int y) {
        int minHeight = std::min(height, image.getHeight() + y); // Height to start iterating from
        int minWidth = std::min(width, image.getWidth() + x); // Width to start iterating from

        int sample_x = -std::min(x, 0); // Height to start iterating from in image
        int sample_y; // Width to start iterating from in image

        for (int i = std::max(x, 0); i < minWidth; i++) {
            sample_y = -std::min(y, 0);
            for (int j = std::max(y, 0); j < minHeight; j++) {
                setPixel(i, j,
                         image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0, 0, 0,
                                                                                                    255)); // Set to pure white or pure black
                sample_y++;
            }
            sample_x++;
        }
    }

    void Canvas::pasteImage(Graymap &image, int x, int y) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        for (int i = std::max(x, 0); i < minWidth; i++) {
            sample_y = -std::min(y, 0);
            for (int j = std::max(y, 0); j < minHeight; j++) {
                uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);

                setPixel(i, j, RGBA(temp, temp, temp, 255)); // Set to grayscale
                sample_y++;
            }
            sample_x++;
        }
    }

    void Canvas::pasteImage(Pixmap<RGB> &image, int x, int y) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        for (int i = std::max(x, 0); i < minWidth; i++) {
            sample_y = -std::min(y, 0);
            for (int j = std::max(y, 0); j < minHeight; j++) {
                setPixel(i, j, image.getPixelUnsafe(sample_x,
                                                    sample_y).rgba()); // Simply converts to RGBA; opacity is implicitly 255
                sample_y++;
            }
            sample_x++;
        }
    }

    void Canvas::pasteImage(Pixmap<RGBA> &image, int x, int y) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        for (int i = std::max(x, 0); i < minWidth; i++) {
            sample_y = -std::min(y, 0);
            for (int j = std::max(y, 0); j < minHeight; j++) {
                setPixel(i, j, image.getPixelUnsafe(sample_x, sample_y)); // Boring
                sample_y++;
            }
            sample_x++;
        }
    }

    void Canvas::mixImage(Bitmap &image, int x, int y, ColorUtils::ColorMix mix) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        switch (mix) {
            case ColorUtils::ColorMix::REPLACE: { // Replace everything, opacity and all
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        setPixel(i, j,
                                 (image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0, 0, 0,
                                                                                                             255)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::ADDITION: { // Add colors together
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        setPixel(i, j,
                                 ColorUtils::add(
                                         (image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     255)),
                                         getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::AVERAGE: { // Average colors
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        setPixel(i, j,
                                 ColorUtils::average(
                                         (image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     255)),
                                         getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: { // Multiply colors
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        setPixel(i, j,
                                 ColorUtils::mult(
                                         (image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     255)),
                                         getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::SUBTRACTION: { // Subtract colors
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        setPixel(i, j,
                                 ColorUtils::sub(
                                         (image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     255)),
                                         getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::MERGE: { // Merge RGB data but keep old opacity
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t opacity = getPixelUnsafe(i, j).a;
                        setPixel(i, j,
                                 image.getPixelUnsafe(sample_x, sample_y) ? RGBA(255, 255, 255, opacity) : RGBA(0, 0,
                                                                                                                0,
                                                                                                                opacity));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
        }
    }

    void Canvas::mixImage(Graymap &image, int x, int y, ColorUtils::ColorMix mix) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        switch (mix) {
            case ColorUtils::ColorMix::REPLACE: { // Replace everything, opacity and all
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j, RGBA(temp, temp, temp, 255));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::ADDITION: { // Add colors together
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::add(RGBA(temp, temp, temp, 255),
                                                 getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::AVERAGE: { // Average colors
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::average(RGBA(temp, temp, temp, 255),
                                                     getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }
                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: {
                for (int i = std::max(x, 0); i < minWidth; i++) { // Multiply colors
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::mult(RGBA(temp, temp, temp, 255),
                                                  getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::SUBTRACTION: { // Subtract colors
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::sub(RGBA(temp, temp, temp, 255),
                                                 getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::MERGE: { // Merge RGB data but keep old opacity
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t opacity = getPixelUnsafe(i, j).a;
                        uint8_t temp = image.getPixelUnsafe(sample_x, sample_y);

                        setPixel(i, j, RGBA(temp, temp, temp, opacity));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
        }
    }

    void Canvas::mixImage(RGBMap &image, int x, int y, ColorUtils::ColorMix mix) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        switch (mix) {
            case ColorUtils::ColorMix::REPLACE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j, temp.rgba());
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::ADDITION: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::add(temp.rgba(),
                                                 getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::AVERAGE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::average(temp.rgba(),
                                                     getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }
                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::mult(temp.rgba(),
                                                  getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::SUBTRACTION: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixelUnsafe(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::sub(temp.rgba(),
                                                 getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::MERGE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixelUnsafe(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::merge(temp,
                                                   getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
        }
    }

    void Canvas::mixImage(RGBAMap &image, int x, int y, ColorUtils::ColorMix mix) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        switch (mix) {
            case ColorUtils::ColorMix::REPLACE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j, temp);
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::ADDITION: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::add(temp,
                                                 getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::AVERAGE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::average(temp,
                                                     getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }
                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixelUnsafe(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::mult(temp,
                                                  getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::SUBTRACTION: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixelUnsafe(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::sub(temp,
                                                 getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
            case ColorUtils::ColorMix::MERGE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixelUnsafe(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::merge(temp,
                                                   getPixelUnsafe(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
        }
    }

    void Canvas::fill(Color color) {
        std::fill_n(pixels, area, color.rgba());
    }

    void Canvas::clear() {
        fill(RGBA(255, 255, 255, 0));
    }

    void Canvas::copyFrom(const Bitmap &p, uint8_t opacity) {
        if (p.getWidth() != width || p.getHeight() != height) {
            throw std::logic_error("Pixmaps must be of the same dimensions for copying.");
        } else {
            for (int i = 0; i < p.getWidth(); i++) {
                for (int j = 0; j < p.getHeight(); j++) {
                    setPixel(i, j, p.getPixelUnsafe(i, j) ? RGBA(255, 255, 255, opacity) : RGBA(0, 0, 0, opacity));
                }
            }
        }
    }

    void Canvas::copyFrom(const Graymap &p, uint8_t opacity) {
        if (p.getWidth() != width || p.getHeight() != height) {
            throw std::logic_error("Pixmaps must be of the same dimensions for copying.");
        } else {
            for (int i = 0; i < p.getWidth(); i++) {
                for (int j = 0; j < p.getHeight(); j++) {
                    uint8_t temp = p.getPixelUnsafe(i, j);
                    setPixel(i, j, RGBA(temp, temp, temp, opacity));
                }
            }
        }
    }

    void Canvas::copyFrom(const RGBMap &p, uint8_t opacity) {
        if (p.getWidth() != width || p.getHeight() != height) {
            throw std::logic_error("Pixmaps must be of the same dimensions for copying.");
        } else {
            for (int i = 0; i < p.getWidth(); i++) {
                for (int j = 0; j < p.getHeight(); j++) {
                    RGB temp = p.getPixelUnsafe(i, j);
                    setPixel(i, j, RGBA(temp.r, temp.g, temp.b, opacity));
                }
            }
        }
    }
}
