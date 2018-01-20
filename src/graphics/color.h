#ifndef COLOR_DEFINED_
#define COLOR_DEFINED_

#include <cmath>
#include <iostream>

namespace Vis {

    typedef unsigned char color_base;

    struct RGB;
    struct RGBA;
    struct HSLA;

    class Color;

    struct HSL {
        color_base h;
        color_base s;
        color_base l;

        HSL() {

        }

        HSL(color_base a, color_base b, color_base c) {
            h = a;
            s = b;
            l = c;
        }

        RGB rgb() const;

        RGBA rgba() const;

        HSLA hsla() const;

        friend std::ostream &operator<<(std::ostream &os, HSL c);
    };

    struct HSLA {
        color_base h;
        color_base s;
        color_base l;
        color_base a;

        HSLA() {

        }

        HSLA(color_base aR, color_base b, color_base c, color_base d) {
            h = aR;
            s = b;
            l = c;
            a = d;
        }

        HSL hsl() const;

        RGB rgb() const;

        RGBA rgba() const;

        friend std::ostream &operator<<(std::ostream &os, HSL c);
    };

    struct RGB {
        color_base r;
        color_base g;
        color_base b;

        RGB() {
            r = 0;
            g = 0;
            b = 0;
        }

        RGB(color_base a_, color_base b_, color_base c_) {
            r = a_;
            g = b_;
            b = c_;
        }

        HSL hsl() const;

        HSLA hsla() const;

        RGBA rgba() const;

        friend std::ostream &operator<<(std::ostream &os, RGB c);
    };

    struct RGBA {
        color_base r;
        color_base g;
        color_base b;
        color_base a;

        RGBA() {

        }

        RGBA(color_base aR, color_base bR, color_base c, color_base d) {
            r = aR;
            g = bR;
            b = c;
            a = d;
        }

        HSL hsl() const;

        HSLA hsla() const;

        RGB rgb() const;

        friend std::ostream &operator<<(std::ostream &os, RGBA c);
    };

    class Color {
    private:
        RGBA internal_color;
    public:
        Color();

        Color(RGB rgb);

        Color(RGBA rgba);

        Color(HSL hsl);

        Color(HSLA hsla);

        void setColor(RGB rgb);

        void setColor(RGBA rgba);

        void setColor(HSL hsl);

        void setColor(HSLA hsla);

        RGB rgb() const;

        RGBA rgba() const;

        HSL hsl() const;

        HSLA hsla() const;

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
