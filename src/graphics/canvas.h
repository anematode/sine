//
// Created by Timothy Herchen on 1/26/18.
//

#ifndef VISUALIZATION_CANVAS_H
#define VISUALIZATION_CANVAS_H

#include "pixmap.h"
#include "imageloader.h"
#include "colorutils.h"
#include <cmath>
#include <algorithm>

namespace Sine {
    class Canvas : public Pixmap<RGBA> {
    public:
        Canvas(int width, int height);

        Canvas(const Canvas &p);

        explicit Canvas(const std::string &filename);

        explicit Canvas(const Bitmap &p);

        explicit Canvas(const Graymap &p);

        explicit Canvas(const RGBMap &p);

        explicit Canvas(const RGBAMap &p);

        void pasteImage(Bitmap &image, int x = 0, int y = 0);

        void pasteImage(Graymap &image, int x = 0, int y = 0);

        void pasteImage(RGBMap &image, int x = 0, int y = 0);

        void pasteImage(RGBAMap &image, int x = 0, int y = 0);

        void mixImage(Bitmap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        void mixImage(Graymap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        void mixImage(RGBMap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        void mixImage(RGBAMap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        void copyFrom(const Bitmap &a, uint8_t opacity = 255);

        void copyFrom(const Graymap &a, uint8_t opacity = 255);

        void copyFrom(const RGBMap &a, uint8_t opacity = 255);

        using Pixmap<RGBA>::copyFrom;

        // void copyFrom(const RGBAMap &a);


        void fill(RGBA color);

        void clear();
    };
}


#endif //VISUALIZATION_CANVAS_H
