#include "color.h"

namespace Sine::Graphics {
    const float HSL_FACTOR_M = 256 / 6.0; // Constant factor used a few times

    HSL RGB::hsl() const {
        int minColor = std::min(r, std::min(g, b)); // int to stop overflow
        int maxColor = std::max(r, std::max(g, b));

        int r_c = r;
        int g_c = g;
        int b_c = b;

        color_base lum = (minColor + maxColor) / 2; // Luminance is average of extreme colors
        color_base sat, h;

        if (minColor == maxColor) { // If all colors are equal, saturation is 0
            sat = 0;
        } else {
            if (lum < 128) { // If the luminance is less than 128
                sat = 256 * (maxColor - minColor) / float(maxColor + minColor); // Divide by sum of extremes
            } else {
                sat = 256 * (maxColor - minColor) /
                      float(512.0 - maxColor - minColor); // Otherwise divide by 512 minus sum of extremes
            }

            // Note that either way, sat will never overflow or underflow
        }

        if (r_c == maxColor) {
            // If red is max color
            h = HSL_FACTOR_M * std::fmod((g_c - b_c) / float(maxColor - minColor), 6);
        } else if (g_c == maxColor) {
            // If green is max color
            h = HSL_FACTOR_M * ((b_c - r_c) / float(maxColor - minColor) + 2);
        } else {
            // If blue is max color
            h = HSL_FACTOR_M * ((r_c - g_c) / float(maxColor - minColor) + 4);
        }

        return {h, sat, lum};
    }

    // Algorithm shamelessly stolen from https://stackoverflow.com/a/9493060/7333670
    float hueToRGB(float p, float q, float t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1 / 6.0) return p + (q - p) * 6 * t;
        if (t < 1 / 2.0) return q;
        if (t < 2 / 3.0) return p + (q - p) * (2 / 3.0 - t) * 6;
        return p;
    }

    // Algorithm shamelessly stolen from https://stackoverflow.com/a/9493060/7333670
    RGB HSL::rgb() const {
        float h_c = h / 255.0; // Scales down to [0...1]
        float s_c = s / 255.0; // Scales down to [0...1]
        float l_c = l / 255.0; // Scales down to [0...1]

        float q = l_c < 0.5 ? l_c * (1 + s_c) : l_c + s_c - l_c * s_c; // Who even knows what's going on here
        float p = 2 * l_c - q;

        float r_d = hueToRGB(p, q, h_c + 1 / 3.0);
        float g_d = hueToRGB(p, q, h_c);
        float b_d = hueToRGB(p, q, h_c - 1 / 3.0);

        return {(color_base)(r_d * 255), (color_base)(g_d * 255), (color_base)(b_d * 255)};
    }

    // TODO: Make RGB to HSL faster! It's slow af right now, probably because of all the floating point arithmetic.
    // Possible implementation:
    /*

     RGB HSL::rgb() const {
        float r, g, b;
        if (s == 0) {
            r = g = b = l;
        } else {
            float h_l = h / 42.66666;
            int i = std::round(h_l);
            float f = h_l - i;
            int p = l * (256 - (int)s) / 256;
            int q = l * (256 - (int)s * f) / 256;
            int t = l * (256 - (int)s * (1 - f)) / 256;

            switch (i) {
                case 0:
                    r = l;
                    g = t;
                    b = p;
                    break;
                case 1:
                    r = q;
                    g = l;
                    b = p;
                    break;
                case 2:
                    r = p;
                    g = l;
                    b = t;
                    break;
                case 3:
                    r = p;
                    g = q;
                    b = l;
                    break;
                case 4:
                    r = t;
                    g = p;
                    b = l;
                    break;
                case 5:
                default:
                    r = l;
                    g = p;
                    b = q;
                    break;
            }
        }

        return {static_cast<color_base>(r), static_cast<color_base>(g), static_cast<color_base>(b)};
    }

     */

    RGBA HSL::rgba(uint8_t opacity) const {
        RGB temp = rgb(); // Constructs a temporary RGB object, speed concern?

        return {temp.r, temp.g, temp.b, opacity};
    }

    HSLA HSL::hsla(uint8_t opacity) const {
        return {h, s, l, opacity};
    }

    HSL HSLA::hsl() const {
        return {h, s, l};
    }

    RGBA HSLA::rgba() const {
        RGB temp = rgb(); // Constructs a temporary RGB object
        return {temp.r, temp.g, temp.b, a};
    }

    RGB HSLA::rgb() const {
        return HSL(h, s, l).rgb(); // Constructs a temporary HSL object
    }

    HSLA RGB::hsla(uint8_t opacity) const {
        HSL temp = hsl(); // Constructs a temporary HSL object
        return temp.hsla(opacity);
    }

    RGBA RGB::rgba(uint8_t opacity) const {
        return {r, g, b, opacity};
    }

    HSL RGBA::hsl() const {
        RGB temp = rgb(); // Constructs a temporary RGB object
        return temp.hsl();
    }

    RGB RGBA::rgb() const {
        return {r, g, b};
    }

    HSLA RGBA::hsla() const {
        HSL temp = hsl(); // Constructs a temporary HSL object
        return {temp.h, temp.s, temp.l, a};
    }


    std::ostream &operator<<(std::ostream &os, RGB c) {
        os << static_cast<int>(c.r) << ',' << static_cast<int>(c.g) << ',' << static_cast<int>(c.b);
        return os;
    }

    std::ostream &operator<<(std::ostream &os, HSL c) {
        os << static_cast<int>(c.h) << ',' << static_cast<int>(c.s) << ',' << static_cast<int>(c.l);
        return os;
    }

    std::ostream &operator<<(std::ostream &os, RGBA c) {
        os << static_cast<int>(c.r) << ',' << static_cast<int>(c.g) << ',' << static_cast<int>(c.b) << ','
           << static_cast<int>(c.a);
        return os;
    }

    std::ostream &operator<<(std::ostream &os, HSLA c) {
        os << static_cast<int>(c.h) << ',' << static_cast<int>(c.s) << ',' << static_cast<int>(c.l) << ','
           << static_cast<int>(c.a);
        return os;
    }

    Color::Color() {
        internal_color = RGBA();
    }

    Color::Color(RGB a, uint8_t opacity) {
        internal_color = a.rgba(opacity);
    }

    Color::Color(RGBA a) {
        internal_color = a;
    }

    Color::Color(HSL a, uint8_t opacity) {
        internal_color = a.rgba(opacity);
    }

    Color::Color(HSLA a) {
        internal_color = a.rgba();
    }

    void Color::setColor(RGB a) {
        internal_color = a.rgba();
    }

    void Color::setColor(RGBA a) {
        internal_color = a;
    }

    void Color::setColor(HSL a) {
        internal_color = a.rgba();
    }

    void Color::setColor(HSLA a) {
        internal_color = a.rgba();
    }

    RGB Color::rgb() const {
        return internal_color.rgb();
    }

    RGBA Color::rgba() const {
        return internal_color;
    }

    HSL Color::hsl() const {
        return internal_color.hsl();
    }

    HSLA Color::hsla() const {
        return internal_color.hsla();
    }

    std::string Color::css_color() {
        std::string out = "rgba(";
        out += std::to_string(static_cast<int>(internal_color.r));
        out += ',';
        out += std::to_string(static_cast<int>(internal_color.g));
        out += ',';
        out += std::to_string(static_cast<int>(internal_color.b));
        out += ',';
        out += std::to_string(static_cast<int>(internal_color.a));
        out += ')';

        return out;
    }

    std::ostream &operator<<(std::ostream &os, const Color &c) {
        os << c.internal_color;
        return os;
    }

    Color Color::operator*(const Color &b) {
        Color ret;

        ret.internal_color.r = (internal_color.r + b.internal_color.r) / 2;
        ret.internal_color.g = (internal_color.g + b.internal_color.g) / 2;
        ret.internal_color.b = (internal_color.b + b.internal_color.b) / 2;
        ret.internal_color.a = (internal_color.a + b.internal_color.a) / 2;

        return ret;
    }

    Color Color::operator*(double aP) {
        return {RGBA(internal_color.r * aP, internal_color.g * aP, internal_color.b * aP, internal_color.a)};
    }

    Color Color::operator/(double aP) {
        return {RGBA(internal_color.r / aP, internal_color.g / aP, internal_color.b / aP, internal_color.a)};
    }

    Color operator*(double b, const Color &a) {
        return {RGBA(a.internal_color.r * b, a.internal_color.g * b, a.internal_color.b * b, a.internal_color.a)};
    }

    Color::operator RGB() const {
        return rgb();
    }

    Color::operator HSL() const {
        return hsl();
    }

    Color::operator HSLA() const {
        return hsla();
    }

    Color::operator RGBA() const {
        return rgba();
    }
}
