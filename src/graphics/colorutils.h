#ifndef COLOR_UTILS_DEFINED_
#define COLOR_UTILS_DEFINED_

#include "color.h"

namespace Sine::Graphics {
    namespace ColorUtils {
        /**
         * Average two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color average
         */
        RGB average(const RGB &c1, const RGB &c2);

        /**
         * Add two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color addition
         */
        RGB add(const RGB &c1, const RGB &c2);

        /**
         * Subtract two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color subtraction
         */
        RGB sub(const RGB &c1, const RGB &c2);

        /**
         * Multiply color by double
         * @param c1 color
         * @param d double
         * @return Scaled color
         */
        RGB mult(const RGB &c1, double d);

        /**
         * Multiply two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color multiplication
         */
        RGB mult(const RGB &c1, const RGB &c2);

        /**
         * Multiply color by double
         * @param c1 color
         * @param d double
         * @return Scaled color
         */
        RGB mult(double d, const RGB &c1);

        /**
         * Average two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color average
         */
        RGBA average(const RGBA &c1, const RGBA &c2);

        /**
         * Add two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color addition
         */
        RGBA add(const RGBA &c1, const RGBA &c2);

        /**
         * Subtract two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color subtraction
         */
        RGBA sub(const RGBA &c1, const RGBA &c2);

        /**
         * Multiply color by double
         * @param c1 color
         * @param d double
         * @return Scaled color
         */
        RGBA mult(const RGBA &c1, double d);

        /**
         * Multiply two colors
         * @param c1 color 1
         * @param c2 color 2
         * @return Color multiplication
         */
        RGBA mult(const RGBA &c1, const RGBA &c2);

        /**
         * Multiply color by double
         * @param c1 color
         * @param d double
         * @return Scaled color
         */
        RGBA mult(double d, const RGBA &c1);

        /**
         * Merge two colors, where the old opacity is kept but the new RGB is used
         * @param c1 color 1
         * @param c2 color 2
         * @return Merged color
         */
        RGBA merge(const RGBA &c1, const RGBA &c2);

        /**
         * Merge two colors, where the old opacity is kept but the new RGB is used
         * @param c1 color 1
         * @param c2 color 2
         * @return Merged color
         */
        RGBA merge(const RGB &c1, const RGBA &c2);

        /**
         * Merge two colors, where the old opacity is kept but the new RGB is used
         * @param c1 color 1
         * @param c2 color 2
         * @return Merged color
         */
        RGBA merge(const RGBA &c1, const RGB &c2);

        /**
         * Saturate color
         * @param c color
         * @param d saturation amount
         * @return Saturated color
         */
        HSL saturate(const HSL &c, int d);

        /**
         * Desaturate color
         * @param c color
         * @param d desaturation amount
         * @return Desaturated color
         */
        HSL desaturate(const HSL &c, int d);

        /**
         * Lighten color
         * @param c color
         * @param d lightening amount
         * @return Lightened color
         */
        HSL lighten(const HSL &c, int d);

        /**
         * Darken color
         * @param c color
         * @param d lightening amount
         * @return Darkened color
         */
        HSL darken(const HSL &c, int d);

        /**
         * Saturate color
         * @param c color
         * @param d saturation amount
         * @return Saturated color
         */
        HSLA saturate(const HSLA &c, int d);

        /**
         * Desaturate color
         * @param c color
         * @param d desaturation amount
         * @return Desaturated color
         */
        HSLA desaturate(const HSLA &c, int d);

        /**
         * Lighten color
         * @param c color
         * @param d lightening amount
         * @return Lightened color
         */
        HSLA lighten(const HSLA &c, int d);

        /**
         * Darken color
         * @param c color
         * @param d lightening amount
         * @return Darkened color
         */
        HSLA darken(const HSLA &c, int d);

        /**
         * Extract luminance from color.
         * @param rgb color
         * @return luminance
         */
        color_base getLuminance(const RGB &rgb);

        /**
         * Extract luminance from color.
         * @param rgba color
         * @return luminance
         */
        color_base getLuminance(const RGBA &rgba);

        /**
         * Extract luminance from color.
         * @param hsl color
         * @return luminance
         */
        color_base getLuminance(const HSL &hsl);

        /**
         * Extract luminance from color.
         * @param hsla color
         * @return luminance
         */
        color_base getLuminance(const HSLA &hsla);

        /**
         * Extract opacity from color.
         * @param rgb color
         * @return opacity
         */
        color_base getOpacity(const RGB &rgb);

        /**
         * Extract opacity from color.
         * @param hsl color
         * @return opacity
         */
        color_base getOpacity(const HSL &hsl);

        /**
         * Extract opacity from color.
         * @param hsla color
         * @return opacity
         */
        color_base getOpacity(const HSLA &hsla);

        /**
         * Extract opacity from color.
         * @param rgba color
         * @return opacity
         */
        color_base getOpacity(const RGBA &rgba);

        /// Defines how to mix colors
        enum class ColorMix {
            AVERAGE, ///< Average colors
            AVG = static_cast<int>(AVERAGE),
            ADDITION, ///< Add colors
            ADD = static_cast<int>(ADDITION),
            MULTIPLICATION, ///< Multiply colors
            MULTIPLY = static_cast<int>(MULTIPLICATION),
            MULT = static_cast<int>(MULTIPLICATION),
            MUL = static_cast<int>(MULT),
            SUBTRACTION, ///< Subtract colors
            SUBTRACT = static_cast<int>(SUBTRACTION),
            SUB = static_cast<int>(SUBTRACTION),
            REPLACE, ///< Replace all color data
            MERGE ///< Use old opacity, new RGB
        };
    }
}


#endif
