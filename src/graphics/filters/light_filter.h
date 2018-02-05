#ifndef LIGHT_FILTER_DEFINED_
#define LIGHT_FILTER_DEFINED_

#include "filter.h"
#include "../colorutils.h"

namespace Sine::Graphics {
    namespace Filters {

        // TODO: Redesign Lighten
        class Lighten : public Filter {
        private:
            int amount;
        public:
            Lighten(int amt = 0);

            void applyTo(Graymap &p);

            void applyTo(RGBMap &p);

            void applyTo(RGBAMap &p);
        };

        Lighten::Lighten(int amt) {
            amount = amt;
        }

        void Lighten::applyTo(Graymap &p) {
            for (unsigned char &a : p) {
                a += amount;
            }
        }

        void Lighten::applyTo(RGBMap &p) {
            for (RGB &a : p) {
                int temp = a.r + amount;
                a.r = (temp > 255) ? 255 : temp;
                temp = a.g + amount;
                a.g = (temp > 255) ? 255 : temp;
                temp = a.b + amount;
                a.b = (temp > 255) ? 255 : temp;
            }
        }

        void Lighten::applyTo(RGBAMap &p) {
            for (RGBA &a : p) {
                int temp = a.r + amount;
                a.r = (temp > 255) ? 255 : temp;
                temp = a.g + amount;
                a.g = (temp > 255) ? 255 : temp;
                temp = a.b + amount;
                a.b = (temp > 255) ? 255 : temp;
            }
        }

        class Darken : public Filter {
        private:
            int amount;
        public:
            Darken(int amt = 0);

            void applyTo(Graymap &p);

            void applyTo(RGBMap &p);

            void applyTo(RGBAMap &p);
        };

        Darken::Darken(int amt) {
            amount = amt;
        }

        void Darken::applyTo(RGBMap &p) {
            for (RGB &a : p) {
                int temp = a.r - amount;
                a.r = (temp < 0) ? 0 : temp;
                temp = a.g - amount;
                a.g = (temp < 0) ? 0 : temp;
                temp = a.b - amount;
                a.b = (temp < 0) ? 0 : temp;
            }
        }

        void Darken::applyTo(RGBAMap &p) {
            for (RGBA &a : p) {
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
