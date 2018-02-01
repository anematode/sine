#ifndef IMAGE_CONVERTER_DEFINED_
#define IMAGE_CONVERTER_DEFINED_

#include <memory>
#include "pixmap.h"

namespace Sine {
    enum class ImageConversionParam {
        AVERAGE,
        AVG = static_cast<int>(AVERAGE),
        LUMINOSITY,
        LUM = static_cast<int>(LUMINOSITY)
    };

    template<typename TypeA, ImageConversionParam opt = ImageConversionParam::LUM>
    struct ImageConverter {
        static TypeA convert(const RGBMap &a);

        static TypeA convert(const RGBAMap &a);

        static TypeA convert(const Bitmap &a);

        static TypeA convert(const Graymap &a);
    };

    template<>
    inline RGBMap ImageConverter<RGBMap>::convert(const RGBAMap &a) {

        int width = a.getWidth();
        int height = a.getHeight();

        std::cout << width << ' ' << height << '\n';

        RGBMap image_ret(width, height);
        for (int i = 0; i < a.getArea(); i++) {
            image_ret.setPixel(i, a.getPixel(i).rgb());
        }

        std::cout << "Udd" << std::endl;

        return image_ret;
    }

    template<>
    inline RGBAMap ImageConverter<RGBAMap>::convert(const RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        RGBAMap image_ret{width, height};
        for (int i = 0; i < a.getArea(); i++) {
            image_ret.setPixel(i, a.getPixel(i).rgba());
        }

        return image_ret;
    }

    template<>
    inline Graymap ImageConverter<Graymap, ImageConversionParam::AVERAGE>::convert(const RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Graymap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);
            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret.setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    inline Graymap ImageConverter<Graymap, ImageConversionParam::LUMINOSITY>::convert(const RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Graymap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);
            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret.setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    inline Graymap ImageConverter<Graymap, ImageConversionParam::AVERAGE>::convert(const RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Graymap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);
            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret.setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    inline Graymap ImageConverter<Graymap, ImageConversionParam::LUMINOSITY>::convert(const RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Graymap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);
            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret.setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    inline RGBMap ImageConverter<RGBMap>::convert(const Graymap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        RGBMap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i);
            image_ret.setPixel(i, RGB(temp, temp, temp));
        }

        return image_ret;
    }

    template<>
    inline RGBAMap ImageConverter<RGBAMap>::convert(const Graymap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        RGBAMap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i);
            image_ret.setPixel(i, RGBA(temp, temp, temp, 255));
        }

        return image_ret;
    }

    template<>
    inline RGBAMap ImageConverter<RGBAMap>::convert(const Bitmap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        RGBAMap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i) ? 255 : 0;
            image_ret.setPixel(i, RGBA(temp, temp, temp, 255));
        }

        return image_ret;
    }

    template<>
    inline RGBMap ImageConverter<RGBMap>::convert(const Bitmap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        RGBMap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i) ? 255 : 0;
            image_ret.setPixel(i, RGB(temp, temp, temp));
        }

        return image_ret;
    }

    template<>
    inline Graymap ImageConverter<Graymap>::convert(const Bitmap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Graymap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i) ? 255 : 0;
            image_ret.setPixel(i, temp);
        }

        return image_ret;
    }

    template<>
    inline Bitmap ImageConverter<Bitmap, ImageConversionParam::AVERAGE>::convert(const RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Bitmap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);

            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret.setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    inline Bitmap ImageConverter<Bitmap, ImageConversionParam::LUMINOSITY>::convert(const RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Bitmap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);

            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret.setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    inline Bitmap ImageConverter<Bitmap, ImageConversionParam::AVERAGE>::convert(const RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Bitmap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);

            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret.setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    inline Bitmap ImageConverter<Bitmap, ImageConversionParam::LUMINOSITY>::convert(const RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Bitmap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);

            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret.setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    inline Bitmap ImageConverter<Bitmap>::convert(const Graymap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        Bitmap image_ret{width, height};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i);
            image_ret.setPixel(i, temp > 128);
        }

        return image_ret;
    }
}

#endif
