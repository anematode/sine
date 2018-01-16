#ifndef SATURATE_FILTER_DEFINED_
#define SATURATE_FILTER_DEFINED_

#include "filter.h"
#include "../colorutils.h"

namespace Vis {
  namespace Filters {
    class Saturate : public Filter {
    private:
      int saturation;
    public:
      Saturate(int amount = 0);

      void applyTo(RGBMap& p);
      void applyTo(RGBAMap& p);
    };

    Saturate::Saturate(int amount) {
      saturation = amount;
    }

    void Saturate::applyTo(RGBMap& p) {
      for (RGB& a : p) {
        a = ColorUtils::saturate(a.hsl(), saturation).rgb();
      }
    }

    void Saturate::applyTo(RGBAMap& p) {
      unsigned char opacity;
      for (RGBA& a : p) {
        opacity = a.a;
        a = ColorUtils::saturate(a.hsl(), saturation).rgba();
        a.a = opacity;
      }
    }

    class Desaturate {
    private:
      int desaturation;
    public:
      Desaturate(int amount = 0);

      void applyTo(RGBMap& p);
      void applyTo(RGBAMap& p);
    };

    Desaturate::Desaturate(int amount) {
      desaturation = amount;
    }

    void Desaturate::applyTo(RGBMap& p) {
      for (RGB& a : p) {
        a = ColorUtils::desaturate(a.hsl(), desaturation).rgb();
      }
    }

    void Desaturate::applyTo(RGBAMap& p) {
      unsigned char opacity;
      for (RGBA& a : p) {
        opacity = a.a;
        a = ColorUtils::desaturate(a.hsl(), desaturation).rgba();
        a.a = opacity;
      }
    }
}
}

#endif
