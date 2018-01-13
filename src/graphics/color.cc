#include "color.h"

namespace Vis {
  const float HSL_FACTOR_M = 256 / 6.0;

  HSL RGB::hsl() const {
    int minColor = std::min(r, std::min(g, b)); // int to stop overflow
    int maxColor = std::max(r, std::max(g, b));

    int r_c = r;
    int g_c = g;
    int b_c = b;

    color_base lum = (minColor + maxColor) / 2;
    color_base sat, hue;

    if (minColor == maxColor) {
      sat = 0;
    } else {
      if (lum < 128) {
        sat = 256 * (maxColor - minColor) / float(maxColor + minColor);
      } else {
        sat = 256 * (maxColor - minColor) / float(512.0 - maxColor - minColor);
      }
    }

    if (r_c == maxColor) {
      hue = HSL_FACTOR_M * std::fmod((g_c - b_c) / float(maxColor - minColor), 6);
    } else if (g_c == maxColor) {
      hue = HSL_FACTOR_M * ((b_c - r_c) / float(maxColor - minColor) + 2);
    } else {
      hue = HSL_FACTOR_M * (4.0 + (r_c - g_c) / float(maxColor - minColor));
    }

    return HSL(hue, sat, lum);
  }

  float hueToRGB(float p, float q, float t) {
      if (t < 0) t += 1;
      if (t > 1) t -= 1;
      if (t < 1/6.0) return p + (q - p) * 6 * t;
      if (t < 1/2.0) return q;
      if (t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
      return p;
    }

  RGB HSL::rgb() const {
    float h_c = h / 256.0;
    float s_c = s / 256.0;
    float l_c = l / 256.0;

    float q = l_c < 0.5 ? l_c * (1 + s_c) : l_c + s_c - l_c * s_c;
    float p = 2 * l_c - q;
    float r_d = hueToRGB(p, q, h_c + 1 / 3.0);
    float g_d = hueToRGB(p, q, h_c);
    float b_d = hueToRGB(p, q, h_c - 1 / 3.0);

    return RGB(r_d * 255, g_d * 255, b_d * 255);
  }

  RGBA HSL::rgba() const {
    RGB temp = rgb();

    return RGBA(temp.r, temp.g, temp.b, 255);
  }

  HSLA HSL::hsla() const {
    return HSLA(h, s, l, 255);
  }

  HSL HSLA::hsl() const {
    return HSL(h, s, l);
  }

  RGBA HSLA::rgba() const {
    RGB temp = rgb();
    return RGBA(temp.r, temp.g, temp.b, a);
  }

  RGB HSLA::rgb() const {
    return HSL(h, s, l).rgb();
  }

  HSLA RGB::hsla() const {
    HSL temp = hsl();
    return temp.hsla();
  }

  RGBA RGB::rgba() const {
    return RGBA(r, g, b, 255);
  }

  HSL RGBA::hsl() const {
    RGB temp = rgb();
    return temp.hsl();
  }

  RGB RGBA::rgb() const {
    return RGB(r, g, b);
  }

  HSLA RGBA::hsla() const {
    HSL temp = hsl();
    return HSLA(temp.h, temp.s, temp.l, 255);
  }


  std::ostream& operator<<(std::ostream& os, RGB c) {
    os << static_cast<int>(c.r) << ',' << static_cast<int>(c.g) << ',' << static_cast<int>(c.b);
    return os;
  }

  std::ostream& operator<<(std::ostream& os, HSL c) {
    os << static_cast<int>(c.h) << ',' << static_cast<int>(c.s) << ',' << static_cast<int>(c.l);
    return os;
  }

  std::ostream& operator<<(std::ostream& os, RGBA c) {
    os << static_cast<int>(c.r) << ',' << static_cast<int>(c.g) << ',' << static_cast<int>(c.b) << ',' << static_cast<int>(c.a);
    return os;
  }

  std::ostream& operator<<(std::ostream& os, HSLA c) {
    os << static_cast<int>(c.h) << ',' << static_cast<int>(c.s) << ',' << static_cast<int>(c.l) << ',' << static_cast<int>(c.a);
    return os;
  }

  Color::Color() {

  }

  Color::Color(RGB a) {
    internal_color = a.rgba();
  }

  Color::Color(RGBA a) {
    internal_color = a;
  }

  Color::Color(HSL a) {
    internal_color = a.rgba();
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
    out += static_cast<int>(internal_color.r);
    out += ',';
    out += static_cast<int>(internal_color.g);
    out += ',';
    out += static_cast<int>(internal_color.b);
    out += ',';
    out += static_cast<float>(internal_color.a / 256.);
    out += ')';

    return out;
  }

  std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << c.internal_color;
    return os;
  }

  Color Color::operator*(const Color& b) {
    Color ret;

    ret.internal_color.r = (internal_color.r + b.internal_color.r) / 2;
    ret.internal_color.g = (internal_color.g + b.internal_color.g) / 2;
    ret.internal_color.b = (internal_color.b + b.internal_color.b) / 2;
    ret.internal_color.a = (internal_color.a + b.internal_color.a) / 2;

    return ret;
  }

  Color Color::operator*(double aP) {
    return Color(RGBA(internal_color.r * aP, internal_color.g * aP, internal_color.b * aP, internal_color.a));
  }

  Color Color::operator/(double aP) {
    return Color(RGBA(internal_color.r / aP, internal_color.g / aP, internal_color.b / aP, internal_color.a));
  }

  Color operator*(double b, const Color& a) {
    return Color(RGBA(a.internal_color.r * b, a.internal_color.g * b, a.internal_color.b * b, a.internal_color.a));
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
