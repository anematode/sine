#ifndef LIGHT_FILTER_DEFINED_
#define LIGHT_FILTER_DEFINED_

#include "filter.h"
#include "../mask.h"
#include "../colorutils.h"

namespace Vis {
  namespace Filters {
    class Lighten : public Filter {
    private:
      int amount;
    public:
      Lighten(int amt = 0);

      void applyTo(Graymap& p);
      void applyTo(RGBMap& p);
      void applyTo(RGBAMap& p);

      void applyTo(Graymask& p);
      void applyTo(RGBMask& p);
      void applyTo(RGBAMask& p);
    };

    Lighten::Lighten(int amt) {
      amount = amt;
    }

    void Lighten::applyTo(Graymap& p) {
      for (unsigned char& a : p) {
        a += amount;
      }
    }

    void Lighten::applyTo(RGBMap& p) {
      for (RGB& a : p) {
        int temp = a.r + amount;
        a.r = (temp > 255) ? 255 : temp;
        temp = a.g + amount;
        a.g = (temp > 255) ? 255 : temp;
        temp = a.b + amount;
        a.b = (temp > 255) ? 255 : temp;
      }
    }

    void Lighten::applyTo(RGBAMap& p) {
      for (RGBA& a : p) {
        int temp = a.r + amount;
        a.r = (temp > 255) ? 255 : temp;
        temp = a.g + amount;
        a.g = (temp > 255) ? 255 : temp;
        temp = a.b + amount;
        a.b = (temp > 255) ? 255 : temp;
      }
    }

    void Lighten::applyTo(Graymask& p) {
      for (int i = 0; i < p.getArea(); i++) {
        p.setPixel(i, p.getPixel(i) + amount);
      }
    }

    void Lighten::applyTo(RGBMask& p) {
      for (int i = 0; i < p.getArea(); i++) {
        if (p.pixelAllowed(i)) {
          RGB a = p.getPixel(i);
          int temp = a.r + amount;
          a.r = (temp > 255) ? 255 : temp;
          temp = a.g + amount;
          a.g = (temp > 255) ? 255 : temp;
          temp = a.b + amount;
          a.b = (temp > 255) ? 255 : temp;

          p.setPixel(i, a, false);
        }
      }
    }

    void Lighten::applyTo(RGBAMask& p) {
      for (int i = 0; i < p.getArea(); i++) {
        if (p.pixelAllowed(i)) {
          RGBA a = p.getPixel(i);
          int temp = a.r + amount;
          a.r = (temp > 255) ? 255 : temp;
          temp = a.g + amount;
          a.g = (temp > 255) ? 255 : temp;
          temp = a.b + amount;
          a.b = (temp > 255) ? 255 : temp;

          p.setPixel(i, a, false);
        }
      }
    }

    class Darken : public Filter {
    private:
      int amount;
    public:
      Darken(int amt = 0);

      void applyTo(Graymap& p);
      void applyTo(RGBMap& p);
      void applyTo(RGBAMap& p);
    };

    Darken::Darken(int amt) {
      amount = amt;
    }

    void Darken::applyTo(RGBMap& p) {
      for (RGB& a : p) {
        int temp = a.r - amount;
        a.r = (temp < 0) ? 0 : temp;
        temp = a.g - amount;
        a.g = (temp < 0) ? 0 : temp;
        temp = a.b - amount;
        a.b = (temp < 0) ? 0 : temp;
      }
    }

    void Darken::applyTo(RGBAMap& p) {
      for (RGBA& a : p) {
        int temp = a.r - amount;
        a.r = (temp < 0) ? 0 : temp;
        temp = a.g - amount;
        a.g = (temp < 0) ? 0 : temp;
        temp = a.b - amount;
        a.b = (temp < 0) ? 0 : temp;
      }
    }
}
}

#endif
