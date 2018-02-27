//
// Created by Timothy Herchen on 1/26/18.
//

#ifndef VISUALIZATION_CANVAS_H
#define VISUALIZATION_CANVAS_H

#include "pixmap.h"
#include "imageloader.h"
#include "colorutils.h"
#include <cmath>
#include <type_traits>
#include <algorithm>

namespace Sine::Graphics {

    enum class Alias {
        ALIASED,
        ANTIALIASED
    };

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
         * Given a functor func which takes 1. a reference to a pixel and 2. a const reference to another pixel,
         * and which sets the first reference to something, apply the functor to mix two images together.
         *
         * @tparam T Pixel type of Pixmap
         * @tparam Func Type of functor
         * @param image Pixmap instance
         * @param func Functor
         * @param x X coordinate of paste position
         * @param y Y coordinate of paste position
         */
        template<typename T, typename Func>
        inline void mixImageByFunction(const Pixmap<T> &image, Func func, int x = 0, int y = 0) {
            int minHeight = std::min(height, image.getHeight() + y); // Height to start iterating from
            int minWidth = std::min(width, image.getWidth() + x); // Width to start iterating from

            int sample_x = -std::min(x, 0); // Height to start iterating from in image
            int sample_y; // Width to start iterating from in image

            for (int i = std::max(x, 0); i < minWidth; i++) {
                sample_y = -std::min(y, 0);
                for (int j = std::max(y, 0); j < minHeight; j++) {
                    func(getPixelUnsafe(i, j), image.getPixelUnsafe(sample_x, sample_y));
                    sample_y++;
                }
                sample_x++;
            }
        };

        /**
         * Succulent templated function which merges an image based on a few predefined methods.
         * @tparam mix Mix type
         * @tparam T Pixel type of Pixmap
         * @param image Pixmap instance
         * @param x X coordinate of pasted position
         * @param y Y coordinate of pasted position
         */
        template<ColorUtils::ColorMix mix = ColorUtils::ColorMix::MERGE, typename T>
        void mixImage(const Pixmap<T> &image, int x = 0, int y = 0) {
            typename ColorUtils::ColorMixFunctor<mix>::internal udder;

            mixImageByFunction(image, udder.func, x, y);
        }

        template<typename C>
        inline void mergePixel(int x, int y, const C &color) {
            setPixelUnsafe(x, y, ColorUtils::merge(ColorUtils::getColor<RGBA>(color), getPixel(x, y)));
        }

        template<typename C>
        inline void mergePixelUnsafe(int x, int y, const C &color) {
            setPixelNoThrow(x, y, ColorUtils::merge(ColorUtils::getColor<RGBA>(color), getPixel(x, y)));
        }

        template<typename C>
        inline void mergePixelNoThrow(int x, int y, const C &color) {
            if (pairContained(x, y)) {
                mergePixelUnsafe(x, y, color);
            }
        }

#define aliasSelector(name, aliased, antialiased) template <Alias alias = Alias::ANTIALIASED, class ... Types> \
        inline void name(Types ... args) { \
            if constexpr (alias == Alias::ALIASED) { \
                aliased(args...); \
            } \
 \
            if constexpr (alias == Alias::ANTIALIASED) { \
                antialiased(args...); \
            } \
        }

        aliasSelector(drawLine, drawLineAliased, drawLineAntialiased);

        aliasSelector(drawThickLine, drawThickLineAliased, drawThickLineAntialiased);

        aliasSelector(drawQuadraticBezier, drawQuadraticBezierAliased, drawQuadraticBezierAntialiased);

        aliasSelector(drawCircle, drawCircleAliased, drawCircleAntialiased);

        virtual void drawLineAliased(float x1, float y1, float x2, float y2, const RGBA &color = Colors::BLACK);

        virtual void drawLineAntialiased(float x1, float y1, float x2, float y2, const RGBA &color = Colors::BLACK);

        virtual void drawThickLineAliased(float x1, float y1, float x2, float y2, float thickness,
                                  const RGBA &color = Colors::BLACK);

        virtual void drawThickLineAntialiased(float x1, float y1, float x2, float y2, float thickness,
                                              const RGBA &color = Colors::BLACK);

        virtual void drawQuadraticBezierAliased(float x1, float y1, float x2, float y2, float x3, float y3,
                                                const RGBA &color = Colors::BLACK);

        virtual void drawQuadraticBezierAntialiased(float x1, float y1, float x2, float y2, float x3, float y3,
                                                    const RGBA &color = Colors::BLACK);

        virtual void drawCircleAliased(float x1, float y1, int r, const RGBA &color = Colors::BLACK);

        virtual void drawCircleAntialiased(float x1, float y1, float r, const RGBA &color = Colors::BLACK);

        virtual void drawThickCircleAliased(float x1, float y1, int r, float thickness, const RGBA &color);

        virtual void drawFilledCircle(float x1, float y1, int r, const RGBA &color = Colors::BLACK);

        virtual void fillRect(int x1, int y1, int x2, int y2, const RGBA &color);

        virtual Canvas smooth_sample(double d = 0.5);

        /**
         * Uses Pixmap<RGBA> copying.
         */
        using Pixmap<RGBA>::copyFrom;

        // Simple copy and move constructors
        virtual Canvas &operator=(const Canvas &c);

        virtual Canvas &operator=(Canvas &&c) noexcept;

        using Pixmap<RGBA>::Pixmap;

        /**
         * Fills the entire canvas uniformly with a given color.
         * @param color Color fill.
         */
        virtual void fill(Color color);

        /**
         * Fills the entire canvas with a completely transparent (i.e. opacity 0) white.
         */
        virtual void clear();

        /**
         * Applies a little blur to the canvas so it looks nicer
         */
        virtual void fuzz();

        virtual Canvas spatialAntialias();
    };
}


#endif //VISUALIZATION_CANVAS_H
