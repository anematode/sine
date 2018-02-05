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

namespace Sine::Graphics {
    /**
     * Canvas class inheriting from RGBAMap that allows more specific and natural operations than a generic Pixmap.
     */
    class Canvas : public Pixmap<RGBA> {
    public:
        /**
         * Constructor initializing blank Canvas with dimensions width x height.
         * @param width Canvas width.
         * @param height Canvas height.
         */
        Canvas(int width, int height);

        /**
         * Copy constructor from Canvas instance.
         * @param canvas Copied Canvas instance.
         */
        Canvas(const Canvas &canvas);

        /**
         * Constructor which automatically loads the Canvas from a file.
         * @param filename Path to the file.
         */
        explicit Canvas(const std::string &filename);

        /**
         * Constructor copying from a Bitmap.
         * @param p Bitmap instance.
         */
        explicit Canvas(const Bitmap &bitmap);

        /**
         * Constructor copying from a Graymap.
         * @param graymap Graymap instance.
         */
        explicit Canvas(const Graymap &graymap);

        /**
         * Constructor copying from an RGBMap.
         * @param rgbmap RGBMap instance.
         */
        explicit Canvas(const RGBMap &rgbmap);

        /**
         * Constructor copying from an RGBAMap.
         * @param rgbamap RGBAMap instance.
         */
        explicit Canvas(const RGBAMap &rgbamap);

        /**
         * Safely pastes a Bitmap at position (x, y), with the top left of the Bitmap coinciding with (x, y).
         * @param image Bitmap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         */
        void pasteImage(Bitmap &image, int x = 0, int y = 0);

        /**
         * Safely pastes a Graymap at position (x, y), with the top left of the Graymap coinciding with (x, y).
         * @param image Graymap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         */
        void pasteImage(Graymap &image, int x = 0, int y = 0);

        /**
         * Safely pastes a RGBMap at position (x, y), with the top left of the RGBMap coinciding with (x, y).
         * @param image RGBMap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         */
        void pasteImage(RGBMap &image, int x = 0, int y = 0);

        /**
         * Safely pastes a RGBAMap at position (x, y), with the top left of the RGBAMap coinciding with (x, y).
         * @param image RGBAMap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         */
        void pasteImage(RGBAMap &image, int x = 0, int y = 0);

        /**
         * Mixes a Bitmap at position (x, y), with the top left of the Bitmap coinciding with (x, y).
         * @param image Bitmap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         * @param mix Type of mix.
         */
        void mixImage(Bitmap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        /**
         * Mixes a Graymap at position (x, y), with the top left of the Graymap coinciding with (x, y).
         * @param image Graymap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         * @param mix Type of mix.
         */
        void mixImage(Graymap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        /**
         * Mixes a RGBMap at position (x, y), with the top left of the RGBMap coinciding with (x, y).
         * @param image RGBMap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         * @param mix Type of mix.
         */
        void mixImage(RGBMap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        /**
         * Mixes a RGBAMap at position (x, y), with the top left of the RGBAMap coinciding with (x, y).
         * @param image RGBAMap instance.
         * @param x X coordinate of paste point.
         * @param y Y coordinate of paste point.
         * @param mix Type of mix.
         */
        void mixImage(RGBAMap &image, int x = 0, int y = 0, ColorUtils::ColorMix mix = ColorUtils::ColorMix::ADDITION);

        /**
         * Copies from Bitmap after construction
         * @param bitmap Bitmap instance.
         * @param opacity Opacity of Canvas after copying.
         */
        void copyFrom(const Bitmap &bitmap, uint8_t opacity = 255);

        /**
         * Copies from Graymap after construction
         * @param graymap Graymap instance.
         * @param opacity Opacity of Canvas after copying.
         */
        void copyFrom(const Graymap &graymap, uint8_t opacity = 255);

        /**
         * Copies from RGBMap after construction
         * @param rgbmap RGBMap instance.
         * @param opacity Opacity of Canvas after copying.
         */
        void copyFrom(const RGBMap &rgbmap, uint8_t opacity = 255);

        /**
         * Uses Pixmap<RGBA> copying.
         */
        using Pixmap<RGBA>::copyFrom;

        /**
         * Fills the entire canvas uniformly with a given color.
         * @param color Color fill.
         */
        void fill(Color color);

        /**
         * Fills the entire canvas with a completely transparent (i.e. opacity 0) white.
         */
        void clear();
    };
}


#endif //VISUALIZATION_CANVAS_H
