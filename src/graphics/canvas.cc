//
// Created by Timothy Herchen on 1/26/18.
//

#include "canvas.h"

namespace Sine {
    Canvas::Canvas(int width, int height) : Pixmap<RGBA>(width, height) {

    }

    Canvas::Canvas(const std::string &filename) : Pixmap<RGBA>(ImageLoader<RGBAMap>::loadAny(filename)) {

    }

    Canvas::Canvas(const Canvas &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        width = p.getWidth();
        height = p.getHeight();

        area = p.area;

        copyFrom(p);
    }

    Canvas::Canvas(const Pixmap<RGBA> &p) : Pixmap<RGBA>(p.getWidth(), p.getHeight()) {
        copyFrom(p);
    }

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
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;

        for (int i = std::max(x, 0); i < minWidth; i++) {
            sample_y = -std::min(y, 0);
            for (int j = std::max(y, 0); j < minHeight; j++) {
                setPixel(i, j,
                         image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0, 0, 0, 255));
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
                uint8_t temp = image.getPixel(sample_x, sample_y);

                setPixel(i, j, RGBA(temp, temp, temp, 255));
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
                setPixel(i, j, image.getPixel(sample_x, sample_y).rgba());
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
                setPixel(i, j, image.getPixel(sample_x, sample_y));
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
            case ColorUtils::ColorMix::REPLACE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        setPixel(i, j,
                                 (image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0, 0, 0,
                                                                                                       255)));
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
                        setPixel(i, j,
                                 ColorUtils::add(
                                         (image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                               0,
                                                                                                               0,
                                                                                                               255)),
                                         getPixel(i, j)));
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
                        setPixel(i, j,
                                 ColorUtils::average(
                                         (image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                               0,
                                                                                                               0,
                                                                                                               255)),
                                         getPixel(i, j)));
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
                        setPixel(i, j,
                                 ColorUtils::mult(
                                         (image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                               0,
                                                                                                               0,
                                                                                                               255)),
                                         getPixel(i, j)));
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
                        setPixel(i, j,
                                 ColorUtils::sub(
                                         (image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, 255) : RGBA(0,
                                                                                                               0,
                                                                                                               0,
                                                                                                               255)),
                                         getPixel(i, j)));
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
                        uint8_t opacity = getPixel(i, j).a;
                        setPixel(i, j,
                                 image.getPixel(sample_x, sample_y) ? RGBA(255, 255, 255, opacity) : RGBA(0, 0,
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
            case ColorUtils::ColorMix::REPLACE: {
                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j, RGBA(temp, temp, temp, 255));
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
                        uint8_t temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::add(RGBA(temp, temp, temp, 255),
                                                 getPixel(i, j)));
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
                        uint8_t temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::average(RGBA(temp, temp, temp, 255),
                                                     getPixel(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }
                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: {
                std::cout << "test" << std::endl;


                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        uint8_t temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::mult(RGBA(temp, temp, temp, 255),
                                                  getPixel(i, j)));
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
                        uint8_t temp = image.getPixel(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::sub(RGBA(temp, temp, temp, 255),
                                                 getPixel(i, j)));
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
                        uint8_t opacity = getPixel(i, j).a;
                        uint8_t temp = image.getPixel(sample_x, sample_y);

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
                        RGB temp = image.getPixel(sample_x, sample_y);
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
                        RGB temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::add(temp.rgba(),
                                                 getPixel(i, j)));
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
                        RGB temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::average(temp.rgba(),
                                                     getPixel(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }
                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: {
                std::cout << "test" << std::endl;


                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGB temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::mult(temp.rgba(),
                                                  getPixel(i, j)));
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
                        RGB temp = image.getPixel(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::sub(temp.rgba(),
                                                 getPixel(i, j)));
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
                        RGB temp = image.getPixel(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::merge(temp,
                                                   getPixel(i, j)));
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
                        RGBA temp = image.getPixel(sample_x, sample_y);
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
                        RGBA temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::add(temp,
                                                 getPixel(i, j)));
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
                        RGBA temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::average(temp,
                                                     getPixel(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }
                break;
            }
            case ColorUtils::ColorMix::MULTIPLICATION: {
                std::cout << "test" << std::endl;


                for (int i = std::max(x, 0); i < minWidth; i++) {
                    sample_y = -std::min(y, 0);
                    for (int j = std::max(y, 0); j < minHeight; j++) {
                        RGBA temp = image.getPixel(sample_x, sample_y);
                        setPixel(i, j,
                                 ColorUtils::mult(temp,
                                                  getPixel(i, j)));
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
                        RGBA temp = image.getPixel(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::sub(temp,
                                                 getPixel(i, j)));
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
                        RGBA temp = image.getPixel(sample_x, sample_y);

                        setPixel(i, j,
                                 ColorUtils::merge(temp,
                                                   getPixel(i, j)));
                        sample_y++;
                    }
                    sample_x++;
                }

                break;
            }
        }
    }

    void Canvas::fill(RGBA color) {
        std::fill_n(pixels, area, color);
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
                    setPixel(i, j, p.getPixel(i, j) ? RGBA(255, 255, 255, opacity) : RGBA(0, 0, 0, opacity));
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
                    uint8_t temp = p.getPixel(i, j);
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
                    RGB temp = p.getPixel(i, j);
                    setPixel(i, j, RGBA(temp.r, temp.g, temp.b, opacity));
                }
            }
        }
    }

    void Canvas::copyFrom(const RGBAMap &p) {
        if (p.getWidth() != width || p.getHeight() != height) {
            throw std::logic_error("Pixmaps must be of the same dimensions for copying.");
        } else {
            for (int i = 0; i < p.getWidth(); i++) {
                for (int j = 0; j < p.getHeight(); j++) {
                    setPixel(i, j, p.getPixel(i, j));
                }
            }
        }
    }

    /*void Canvas::pasteImage(RGBAMap& image, int x, int y) {
        int minHeight = std::min(height, image.getHeight() + y);
        int minWidth = std::min(width, image.getWidth() + x);

        int sample_x = -std::min(x, 0);
        int sample_y;
        RGBA temp;

        for (int i = x; i < minWidth; i++) {
            sample_y = 0;
            for (int j = y; j < minHeight; j++) {
                temp = image.getPixel(sample_x, sample_y, false);

                RGBA& temp_2 = getPixelRef(i, j, false);

                //if (temp.a == 0) continue;
                float f_a = temp.a / 256.0;
                float fs_a = temp_2.a / 256.0;

                int l = f_a * (int)temp.r + fs_a * (int)temp_2.r;
                if (l > 255) l = 255;

                temp_2.r = l;

                l = f_a * (int)temp.g + fs_a * (int)temp_2.g;
                if (l > 255) l = 255;

                temp_2.g = l;

                l = f_a * (int)temp.b + fs_a * (int)temp_2.b;
                if (l > 255) l = 255;

                temp_2.b = l;


                temp_2.a = std::max((int)temp.a + (int)temp_2.a, 255);

                sample_y++;
            }
            sample_x++;
        }

        std::cout << "test\n";
    }*/
}
