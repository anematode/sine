#ifndef COLOR_DEFINED_
#define COLOR_DEFINED_

#include <cmath>
#include <iostream>

namespace Sine::Graphics {

    /*
     * Basic unit of hue, saturation, lightness, red, blue, and green
     */
    typedef uint8_t color_base;

    struct RGB;
    struct RGBA;
    struct HSLA;

    class Color;

    /**
     * Struct representing an HSL (hue, saturation, lightness) color scheme.
     */
    struct HSL {
        color_base h;
        color_base s;
        color_base l;

        /**
         * Default constructor.
         */
        HSL() {
            h = 0;
            s = 0;
            l = 0;
        }

        /**
         * Simple constructor.
         * @param _h hue
         * @param _s saturation
         * @param _l lightness
         */
        HSL(color_base _h, color_base _s, color_base _l) {
            h = _h;
            s = _s;
            l = _l;
        }

        /**
         * Conversion to RGB.
         * @return RGB equivalent (rounded).
         */
        RGB rgb() const;

        /**
         * Conversion to RGBA, given an opacity
         * @param opacity Opacity of returned color.
         * @return RGBA equivalent (rounded).
         */
        RGBA rgba(uint8_t opacity = 255) const;

        /**
         * Conversion to HSLA, given an opacity
         * @param opacity Opacity of returned color.
         * @return HSLA equivalent.
         */
        HSLA hsla(uint8_t opacity = 255) const;

        friend std::ostream &operator<<(std::ostream &os, HSL c);
    };

    /**
     * Struct representing an HSLA (hue, saturation, lightness, opacity) color scheme.
     */
    struct HSLA {
        color_base h;
        color_base s;
        color_base l;
        color_base a;

        /**
         * Default constructor.
         */
        HSLA() {
            h = 0;
            s = 0;
            l = 0;
            a = 0;
        }

        /**
         * Simple constructor
         * @param _h hue
         * @param _s saturation
         * @param _l lightness
         * @param _a opacity
         */
        HSLA(color_base _h, color_base _s, color_base _l, color_base _a = 255) {
            h = _h;
            s = _s;
            l = _l;
            a = _a;
        }

        /**
         * Conversion to HSL.
         * @return HSL equivalent.
         */
        HSL hsl() const;

        /**
         * Conversion to RGB.
         * @return RGB equivalent (rounded).
         */
        RGB rgb() const;

        /**
         * Conversion to RGBA.
         * @return RGBA equivalent (rounded).
         */
        RGBA rgba() const;

        friend std::ostream &operator<<(std::ostream &os, HSL c);
    };

    /**
     * Struct representing an RGB (red, green, blue) color scheme.
     */
    struct RGB {
        color_base r;
        color_base g;
        color_base b;

        /**
         * Default constructor.
         */
        RGB() {
            r = 0;
            g = 0;
            b = 0;
        }

        /**
         * Simple constructor.
         * @param _r red
         * @param _g green
         * @param _b blue
         */
        RGB(color_base _r, color_base _g, color_base _b) {
            r = _r;
            g = _g;
            b = _b;
        }

        /**
         * Conversion to HSL.
         * @return HSL equivalent (rounded).
         */
        HSL hsl() const;

        /**
         * Conversion to HSLA, given an opacity.
         * @param opacity Opacity of returned color.
         * @return HSLA equivalent (rounded).
         */
        HSLA hsla(uint8_t opacity = 255) const;

        /**
         * Conversion to RGBA, given an opacity.
         * @param opacity Opacity of returned color.
         * @return RGBA equivalent.
         */
        RGBA rgba(uint8_t opacity = 255) const;

        friend std::ostream &operator<<(std::ostream &os, RGB c);
    };

    /**
     * Struct representing an RGBA (red, green, blue, opacity) color scheme.
     */
    struct RGBA {
        color_base r;
        color_base g;
        color_base b;
        color_base a;

        /**
         * Default constructor.
         */
        RGBA() {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
        }

        /**
         * Simple constructor.
         * @param _r red
         * @param _g green
         * @param _b blue
         * @param _a opacity
         */
        RGBA(color_base _r, color_base _g, color_base _b, color_base _a) {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

        /**
         * Conversion to HSL.
         * @return HSL equivalent (rounded).
         */
        HSL hsl() const;

        /**
         * Conversion to HSLA.
         * @return HSLA equivalent (rounded).
         */
        HSLA hsla() const;

        /**
         * Conversion to RGB.
         * @return RGB equivalent.
         */
        RGB rgb() const;

        friend std::ostream &operator<<(std::ostream &os, RGBA c);
    };

    /**
     * General color class encapsulating any color type, supporting implicit conversions
     */
    class Color {
    private:
        RGBA internal_color;
    public:
        Color();

        Color(RGB rgb, uint8_t opacity = 255);

        Color(RGBA rgba);

        Color(HSL hsl, uint8_t opacity = 255);

        Color(HSLA hsla);

        void setColor(RGB rgb);

        void setColor(RGBA rgba);

        void setColor(HSL hsl);

        void setColor(HSLA hsla);

        RGB rgb() const;

        RGBA rgba() const;

        HSL hsl() const;

        HSLA hsla() const;

        /**
         * Converts to CSS output... why not.
         * @return String representation of CSS color.
         */
        std::string css_color();

        friend std::ostream &operator<<(std::ostream &os, const Color &c);

        Color operator*(const Color &b);

        Color operator*(double a);

        friend Color operator*(double a, const Color &b);

        Color operator/(double a);

        operator HSL() const;

        operator RGB() const;

        operator HSLA() const;

        operator RGBA() const;
    };

    namespace Colors {
        const Color BLACK = Color(RGB(0, 0, 0));
        const Color WHITE = Color(RGB(255, 255, 255));
        const Color RED = Color(RGB(255, 0, 0));
        const Color GREEN = Color(RGB(0, 255, 0));
        const Color BLUE = Color(RGB(0, 0, 255));
        const Color YELLOW = Color(RGB(255, 255, 0));
        const Color CYAN = Color(RGB(0, 255, 255));
        const Color MAGENTA = Color(RGB(255, 0, 255));
    }

}

#endif
