#ifndef COLOR_UTILS_DEFINED_
#define COLOR_UTILS_DEFINED_

#include "color.h"

namespace Sine {
    namespace ColorUtils {
        inline RGB average(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;

            r += c2.r;
            g += c2.g;
            b += c2.b;

            return {r >> 1, g >> 1, b >> 1};
        }

        inline RGB add(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            r += c2.r;

            int g = c1.g;
            g += c2.g;

            int b = c1.b;
            b += c2.b;

            return {(r > 255) ? 255 : r, (g > 255) ? 255 : g, (b > 255) ? 255 : b};
        }

        inline RGB sub(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            r -= c2.r;

            int g = c1.g;
            g -= c2.g;

            int b = c1.b;
            b -= c2.b;

            return {static_cast<color_base>((r < 0) ? 0 : r), static_cast<color_base>((g < 0) ? 0 : g),
                    static_cast<color_base>((b < 0) ? 0 : b)};
        }

        inline RGB mult(const RGB &c1, double d) {
            int r = (int) (c1.r * d);
            int g = (int) (c1.g * d);
            int b = (int) (c1.b * d);

            return {r, g, b};
        }

        inline RGB mult(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;

            r *= c2.r;
            g *= c2.g;
            b *= c2.b;

            return {r / 256.0, g / 256.0, b / 256.0};
        }

        inline RGB mult(double d, const RGB &c1) {
            return mult(c1, d);
        }

        inline RGBA average(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;
            int a = c1.a;

            r += c2.r;
            g += c2.g;
            b += c2.b;
            a += c2.a;

            return {r >> 1, g >> 1, b >> 1, a >> 1};
        }

        inline RGBA add(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            r += c2.r;

            int g = c1.g;
            g += c2.g;

            int b = c1.b;
            b += c2.b;

            int a = c1.a;
            a += c2.a;

            return {(r > 255) ? 255 : r, (g > 255) ? 255 : g, (b > 255) ? 255 : b, (a > 255) ? 255 : a};
        }

        inline RGBA sub(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            r -= c2.r;

            int g = c1.g;
            g -= c2.g;

            int b = c1.b;
            b -= c2.b;

            int a = c1.a;
            a -= c2.a;

            return {(r < 0) ? 0 : r, (g < 0) ? 0 : g, (b < 0) ? 0 : b, (a < 0) ? 0 : a};
        }

        inline RGBA mult(const RGBA &c1, double d) {
            int r = (int) (c1.r * d);
            int g = (int) (c1.g * d);
            int b = (int) (c1.b * d);
            int a = (int) (c1.a * d);

            return {r, g, b, a};
        }

        inline RGBA mult(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;
            int a = c1.a;

            r *= c2.r;
            g *= c2.g;
            b *= c2.b;
            a *= c2.a;

            return {r / 256, g / 256, b / 256, a / 256};
        }

        inline RGBA mult(double d, const RGBA &c1) {
            return mult(c1, d);
        }

        inline RGBA merge(const RGBA &c1, const RGBA &c2) {
            int opacity = 255 - c1.a;
            int opacity_r = c1.a;

            int r = ((int) c2.r * opacity + (int) c1.r * opacity_r) / 255;

            int g = ((int) c2.g * opacity + (int) c1.g * opacity_r) / 255;

            int b = ((int) c2.b * opacity + (int) c1.b * opacity_r) / 255;

            int a = c1.a + c2.a;

            return {(r > 255) ? 255 : r, (g > 255) ? 255 : g, (b > 255) ? 255 : b, (a > 255) ? 255 : a};
        }

        inline RGBA merge(const RGB &c1, const RGBA &c2) {
            return merge(c1.rgba(), c2);
        }


        inline HSL saturate(const HSL &c, int d) {
            int ns = c.s + d;
            return {c.h, (ns > 255) ? 255 : ns, c.l};
        }

        inline HSL desaturate(const HSL &c, int d) {
            int ns = c.s - d;
            return {c.h, (ns < 0) ? 0 : ns, c.l};
        }

        inline HSL lighten(const HSL &c, int d) {
            int nl = c.l + d;
            return {c.h, c.s, (nl > 255) ? 255 : nl};
        }

        inline HSL darken(const HSL &c, int d) {
            int nl = c.l - d;
            return HSL(c.h, c.s, (nl < 0) ? 0 : nl);
        }

        inline color_base getLuminance(const RGB &rgb) {
            int minColor = std::min(rgb.r, std::min(rgb.g, rgb.b)); // int to stop overflow
            int maxColor = std::max(rgb.r, std::max(rgb.g, rgb.b));

            return (minColor + maxColor) / 2;
        }

        inline color_base getLuminance(const RGBA &rgb) {
            int minColor = std::min(rgb.r, std::min(rgb.g, rgb.b)); // int to stop overflow
            int maxColor = std::max(rgb.r, std::max(rgb.g, rgb.b));

            return (minColor + maxColor) / 2;
        }

        inline color_base getLuminance(const HSL &hsl) {
            return hsl.l;
        }

        inline color_base getLuminance(const HSLA &hsl) {
            return hsl.l;
        }

        inline color_base getOpacity(const RGB &) {
            return 255;
        }

        inline color_base getOpacity(const HSL &) {
            return 255;
        }

        inline color_base getOpacity(const HSLA &hsla) {
            return hsla.a;
        }

        inline color_base getOpacity(const RGBA &rgba) {
            return rgba.a;
        }

        enum class ColorMix {
            AVERAGE,
            AVG = static_cast<int>(AVERAGE),
            ADDITION,
            ADD = static_cast<int>(ADDITION),
            MULTIPLICATION,
            MULTIPLY = static_cast<int>(MULTIPLICATION),
            MULT = static_cast<int>(MULTIPLICATION),
            MUL = static_cast<int>(MULT),
            SUBTRACTION,
            SUBTRACT = static_cast<int>(SUBTRACTION),
            SUB = static_cast<int>(SUBTRACTION),
            REPLACE,
            MERGE
        };
    }
}


#endif
