#ifndef COLOR_UTILS_DEFINED_
#define COLOR_UTILS_DEFINED_

#include "color.h"

namespace Vis {
    namespace ColorUtils {
        RGB average(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;

            r += c2.r;
            g += c2.g;
            b += c2.b;

            return RGB(r >> 1, g >> 1, b >> 1);
        }

        RGB add(const RGB &c1, const RGB &c2) {
            return RGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
        }

        RGB mult(const RGB &c1, double d) {
            return RGB(c1.r * d, c1.g * d, c1.b * d);
        }

        RGB mult(const RGB &c1, const RGB &c2) {
            int r = c1.r;
            int g = c1.g;
            int b = c1.b;

            r *= c2.r;
            g *= c2.g;
            b *= c2.b;

            return RGB(r / 256.0, g / 256.0, b / 256.0);
        }

        RGB mult(double d, const RGB &c1) {
            return RGB(c1.r * d, c1.g * d, c1.b * d);
        }

        HSL saturate(const HSL &c, int d) {
            int ns = c.s + d;
            return HSL(c.h, (ns > 255) ? 255 : ns, c.l);
        }

        HSL desaturate(const HSL &c, int d) {
            int ns = c.s - d;
            return HSL(c.h, (ns < 0) ? 0 : ns, c.l);
        }

        HSL lighten(const HSL &c, int d) {
            int nl = c.l + d;
            return HSL(c.h, c.s, (nl > 255) ? 255 : nl);
        }

        HSL darken(const HSL &c, int d) {
            int nl = c.l - d;
            return HSL(c.h, c.s, (nl < 0) ? 0 : nl);
        }
    }
}


#endif
