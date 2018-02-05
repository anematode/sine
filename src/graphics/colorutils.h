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
         * Merge two colors using opacity info
         * @param c1 color 1
         * @param c2 color 2
         * @return Merged color
         */
        RGBA merge(const RGBA &c1, const RGBA &c2);

        /**
         * Merge two colors using opacity info
         * @param c1 color 1
         * @param c2 color 2
         * @return Merged color
         */
        RGBA merge(const RGB &c1, const RGBA &c2);

        /**
         * Merge two colors using opacity info
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

        /**
         * Extract RGBA from color.
         * @param c color
         * @return RGBA equivalent
         */
        RGBA getRGBA(const RGBA &c);

        /**
         * Extract RGBA from color.
         * @param c color
         * @return RGBA equivalent
         */
        RGBA getRGBA(const RGB &c);

        /**
         * Extract RGBA from color.
         * @param c color
         * @return RGBA equivalent
         */
        RGBA getRGBA(uint8_t c);

        /**
         * Extract RGBA from color.
         * @param c color
         * @return RGBA equivalent
         */
        RGBA getRGBA(bool c);

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
            MERGE ///< Merge colors using opacity info
        };

        namespace Functors {
            inline RGBA replace(const RGBA &c1, const RGBA &c2) {
                return c2;
            }

            /**
             * Functor which averages two colors, writing to the first.
             */

#define GENERATE_FUNCTOR_T(name) struct FUNCTOR_T_ ## name {  \
            void operator() (RGBA &c1, const RGBA &c2) { \
                c1 = name(c1, c2); \
            } \
 \
            void operator() (RGBA &c1, const RGB &c2) { \
                c1 = name(c1, c2.rgba()); \
            } \
 \
            void operator() (RGBA &c1, uint8_t g) { \
                c1 = name(c1, RGBA(g, g, g, 255)); \
            } \
 \
            void operator() (RGBA &c1, bool c) { \
                c1 = name(c1, c ? RGBA(255, 255, 255, 255) : RGBA(255, 255, 255, 0)); \
            } \
        };

            GENERATE_FUNCTOR_T(average);
            /**
             * Functor which averages two colors, writing to the first.
             */
            inline const auto AVERAGE = FUNCTOR_T_average();

            GENERATE_FUNCTOR_T(add);
            /**
             * Functor which adds two colors, writing to the first.
             */
            inline const auto ADDITION = FUNCTOR_T_add();

            GENERATE_FUNCTOR_T(mult);
            /**
             * Functor which multiplies two colors, writing to the first.
             */
            inline const auto MULTIPLY = FUNCTOR_T_mult();

            GENERATE_FUNCTOR_T(sub);
            /**
             * Functor which subtracts two colors, writing to the first.
             */
            inline const auto SUBTRACTION = FUNCTOR_T_sub();

            GENERATE_FUNCTOR_T(replace);
            /**
             * Functor which replaces the first color with the second.
             */
            inline const auto REPLACE = FUNCTOR_T_replace();

            GENERATE_FUNCTOR_T(merge);
            /**
             * Functor which merges the second color into the first color.
             */
            inline const auto MERGE = FUNCTOR_T_merge();
        }

        namespace {

            /**
             * Structure that allows determination of functor type given a mix type
             * @tparam mix Mix type
             */
            template<ColorMix mix>
            struct _ColorMixFunctorType {
                using type = int;
            };

            template<>
            struct _ColorMixFunctorType<ColorMix::AVERAGE> {
                using type = decltype(Functors::AVERAGE);
            };

            template<>
            struct _ColorMixFunctorType<ColorMix::ADDITION> {
                using type = decltype(Functors::ADDITION);
            };

            template<>
            struct _ColorMixFunctorType<ColorMix::MULTIPLY> {
                using type = decltype(Functors::MULTIPLY);
            };

            template<>
            struct _ColorMixFunctorType<ColorMix::SUBTRACTION> {
                using type = decltype(Functors::SUBTRACTION);
            };
            template<>
            struct _ColorMixFunctorType<ColorMix::REPLACE> {
                using type = decltype(Functors::REPLACE);
            };

            template<>
            struct _ColorMixFunctorType<ColorMix::MERGE> {
                using type = decltype(Functors::MERGE);
            };

            /**
             * Container for functor that applies the given ColorMix to two colors
             * @tparam mix
             * @return
             */
            template<ColorMix mix, typename _functor_type>
            struct _ColorMixFunctor {
                static const _functor_type func;
            };

            template<>
            const auto _ColorMixFunctor<ColorMix::AVERAGE, decltype(Functors::AVERAGE)>::func = Functors::AVERAGE;
            template<>
            const auto _ColorMixFunctor<ColorMix::ADDITION, decltype(Functors::ADDITION)>::func = Functors::ADDITION;
            template<>
            const auto _ColorMixFunctor<ColorMix::MULTIPLICATION, decltype(Functors::MULTIPLY)>::func = Functors::MULTIPLY;
            template<>
            const auto _ColorMixFunctor<ColorMix::SUBTRACTION, decltype(Functors::SUBTRACTION)>::func = Functors::SUBTRACTION;
            template<>
            const auto _ColorMixFunctor<ColorMix::REPLACE, decltype(Functors::REPLACE)>::func = Functors::REPLACE;
            template<>
            const auto _ColorMixFunctor<ColorMix::MERGE, decltype(Functors::MERGE)>::func = Functors::MERGE;
        }

        template<ColorMix mix>
        struct ColorMixFunctor {
            typedef _ColorMixFunctor<mix, typename _ColorMixFunctorType<mix>::type> internal;
        };

    }
}


#endif
