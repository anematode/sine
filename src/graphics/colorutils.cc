//
// Created by Timothy Herchen on 2/4/18.
//

#include "colorutils.h"

namespace Sine::Graphics {
    namespace ColorUtils {
        RGB average(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;

            r += c2.r;
            g += c2.g;
            b += c2.b;

            return {static_cast<color_base>(r >> 1), static_cast<color_base>(g >> 1), static_cast<color_base>(b >> 1)};
        }

        RGB add(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            r += c2.r;

            int g = c1.g;
            g += c2.g;

            int b = c1.b;
            b += c2.b;

            return {static_cast<color_base>((r > 255) ? 255 : r), static_cast<color_base>((g > 255) ? 255 : g),
                    static_cast<color_base>((b > 255) ? 255 : b)};
        }

        RGB sub(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            r -= c2.r;

            int g = c1.g;
            g -= c2.g;

            int b = c1.b;
            b -= c2.b;

            return {static_cast<color_base>((r < 0) ? 0 : r), static_cast<color_base>((g < 0) ? 0 : g),
                    static_cast<color_base>((b < 0) ? 0 : b)};
        }

        RGB mult(const RGB &c1, double d) {
            auto r = (int) (c1.r * d);
            auto g = (int) (c1.g * d);
            auto b = (int) (c1.b * d);

            return {static_cast<color_base>(r), static_cast<color_base>(g), static_cast<color_base>(b)};
        }

        RGB mult(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;

            r *= c2.r;
            g *= c2.g;
            b *= c2.b;

            return {static_cast<color_base>(r / 256), static_cast<color_base>(g / 256),
                    static_cast<color_base>(b / 256)};
        }

        RGB mult(double d, const RGB &c1) {
            return mult(c1, d);
        }

        RGBA average(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;
            int a = c1.a;

            r += c2.r;
            g += c2.g;
            b += c2.b;
            a += c2.a;

            return {static_cast<color_base>(r >> 1), static_cast<color_base>(g >> 1), static_cast<color_base>(b >> 1),
                    static_cast<color_base>(a >> 1)};
        }

        RGBA add(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            r += c2.r;

            int g = c1.g;
            g += c2.g;

            int b = c1.b;
            b += c2.b;

            int a = c1.a;
            a += c2.a;

            return {static_cast<color_base>((r > 255) ? 255 : r), static_cast<color_base>((g > 255) ? 255 : g),
                    static_cast<color_base>((b > 255) ? 255 : b), static_cast<color_base>((a > 255) ? 255 : a)};
        }

        RGBA sub(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            r -= c2.r;

            int g = c1.g;
            g -= c2.g;

            int b = c1.b;
            b -= c2.b;

            int a = c1.a;
            a -= c2.a;

            return {static_cast<color_base>((r < 0) ? 0 : r), static_cast<color_base>((g < 0) ? 0 : g),
                    static_cast<color_base>((b < 0) ? 0 : b), static_cast<color_base>((a < 0) ? 0 : a)};
        }

        RGBA mult(const RGBA &c1, double d) {
            auto r = (int) (c1.r * d);
            auto g = (int) (c1.g * d);
            auto b = (int) (c1.b * d);
            auto a = (int) (c1.a * d);

            return {static_cast<color_base>(r), static_cast<color_base>(g), static_cast<color_base>(b),
                    static_cast<color_base>(a)};
        }

        RGBA mult(const RGBA &c1, const RGBA &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;
            int a = c1.a;

            r *= c2.r;
            g *= c2.g;
            b *= c2.b;
            a *= c2.a;

            return {static_cast<color_base>(r / 256), static_cast<color_base>(g / 256),
                    static_cast<color_base>(b / 256), static_cast<color_base>(a / 256)};
        }

        RGBA mult(double d, const RGBA &c1) {
            return mult(c1, d);
        }

        RGBA merge(const RGBA &c1, const RGBA &c2) {
            int opacity = 255 - c1.a;
            int opacity_r = c1.a;

            int r = ((int) c2.r * opacity + (int) c1.r * opacity_r) / 255;

            int g = ((int) c2.g * opacity + (int) c1.g * opacity_r) / 255;

            int b = ((int) c2.b * opacity + (int) c1.b * opacity_r) / 255;

            int a = c1.a + c2.a;

            return {static_cast<color_base>((r > 255) ? 255 : r), static_cast<color_base>((g > 255) ? 255 : g),
                    static_cast<color_base>((b > 255) ? 255 : b), static_cast<color_base>((a > 255) ? 255 : a)};
        }

        RGBA merge(const RGB &c1, const RGBA &c2) {
            return merge(c1.rgba(), c2);
        }

        RGBA merge(const RGBA &c1, const RGB &c2) {
            return merge(c1, c2.rgba());
        }


        HSL saturate(const HSL &c, int d) {
            int ns = c.s + d;
            return {c.h, static_cast<color_base>((ns > 255) ? 255 : ns), c.l};
        }

        HSL desaturate(const HSL &c, int d) {
            int ns = c.s - d;
            return {c.h, static_cast<color_base>((ns < 0) ? 0 : ns), c.l};
        }

        HSL lighten(const HSL &c, int d) {
            int nl = c.l + d;
            return {c.h, c.s, static_cast<color_base>((nl > 255) ? 255 : nl)};
        }

        HSL darken(const HSL &c, int d) {
            int nl = c.l - d;
            return {c.h, c.s, static_cast<color_base>((nl < 0) ? 0 : nl)};
        }

        HSLA saturate(const HSLA &c, int d) {
            int ns = c.s + d;
            return {c.h, static_cast<color_base>((ns > 255) ? 255 : ns), c.l, c.a};
        }

        HSLA desaturate(const HSLA &c, int d) {
            int ns = c.s - d;
            return {c.h, static_cast<color_base>((ns < 0) ? 0 : ns), c.l, c.a};
        }

        HSLA lighten(const HSLA &c, int d) {
            int nl = c.l + d;
            return {c.h, c.s, static_cast<color_base>((nl > 255) ? 255 : nl), c.a};
        }

        HSLA darken(const HSLA &c, int d) {
            int nl = c.l - d;
            return {c.h, c.s, static_cast<color_base>((nl < 0) ? 0 : nl), c.a};
        }

        color_base getLuminance(const RGB &rgb) {
            int minColor = std::min(rgb.r, std::min(rgb.g, rgb.b)); // int to stop overflow
            int maxColor = std::max(rgb.r, std::max(rgb.g, rgb.b));

            return static_cast<color_base>((minColor + maxColor) / 2);
        }

        color_base getLuminance(const RGBA &rgb) {
            int minColor = std::min(rgb.r, std::min(rgb.g, rgb.b)); // int to stop overflow
            int maxColor = std::max(rgb.r, std::max(rgb.g, rgb.b));

            return static_cast<color_base>((minColor + maxColor) / 2);
        }

        color_base getLuminance(const HSL &hsl) {
            return hsl.l;
        }

        color_base getLuminance(const HSLA &hsl) {
            return hsl.l;
        }

        color_base getOpacity(const RGB &) {
            return 255;
        }

        color_base getOpacity(const HSL &) {
            return 255;
        }

        color_base getOpacity(const HSLA &hsla) {
            return hsla.a;
        }

        color_base getOpacity(const RGBA &rgba) {
            return rgba.a;
        }

        template<>
        bool getColor(bool c) {
            return c;
        }

        template<>
        bool getColor(uint8_t c) {
            return (c > 128);
        }

        template<>
        bool getColor(const RGB &c) {
            return ((int) c.r + (int) c.g + (int) c.b) > 384;
        }

        template<>
        bool getColor(const RGBA &c) {
            return ((int) c.r + (int) c.g + (int) c.b) * c.a > 98304;
        }

        template<>
        uint8_t getColor(bool c) {
            return c ? 255 : 0;
        }

        template<>
        uint8_t getColor(uint8_t c) {
            return c;
        }

        template<>
        uint8_t getColor(const RGB &c) {
            return std::floor(((int) c.r + (int) c.g + (int) c.b) / 3.0);
        }

        template<>
        uint8_t getColor(const RGBA &c) {
            return (((int) c.r + (int) c.g + (int) c.b) * c.a) / (255 * 3.0);
        }

        template<>
        RGB getColor(bool c) {
            return c ? RGB(255, 255, 255) : RGB(0, 0, 0);
        }

        template<>
        RGB getColor(uint8_t c) {
            return RGB(c, c, c);
        }

        template<>
        RGB getColor(const RGB &c) {
            return c;
        }

        template<>
        RGB getColor(const RGBA &c) {
            return c.rgb();
        }

        template<>
        RGBA getColor(const RGBA &c) {
            return c;
        }

        template<>
        RGBA getColor(const RGB &c) {
            return c.rgba();
        }

        template<>
        RGBA getColor(uint8_t c) {
            return RGBA(c, c, c, 255);
        }

        template<>
        RGBA getColor(bool c) {
            return (c ? RGBA(255, 255, 255, 255) : RGBA(0, 0, 0, 255));
        }
    }
}