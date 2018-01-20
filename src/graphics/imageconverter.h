#ifndef IMAGE_CONVERTER_DEFINED_
#define IMAGE_CONVERTER_DEFINED_

#include <memory>
#include "pixmap.h"

namespace Vis {

    enum class ImageConversionParam {
        AVERAGE,
        AVG = AVERAGE,
        LUMINOSITY,
        LUM = LUMINOSITY
    };

    template<typename TypeA, ImageConversionParam opt = ImageConversionParam::LUM>
    struct ImageConverter {
        static std::unique_ptr<TypeA> convert(RGBMap &a);

        static std::unique_ptr<TypeA> convert(RGBAMap &a);

        static std::unique_ptr<TypeA> convert(Bitmap &a);

        static std::unique_ptr<TypeA> convert(Graymap &a);
    };

    template<>
    std::unique_ptr<RGBMap> ImageConverter<RGBMap>::convert(RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<RGBMap> image_ret{new RGBMap(width, height)};
        for (int i = 0; i < a.getWidth(); i++) {
            for (int j = 0; j < a.getHeight(); j++) {
                image_ret->setPixel(i, j, a.getPixel(i, j).rgb());
            }
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<RGBAMap> ImageConverter<RGBAMap>::convert(RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<RGBAMap> image_ret{new RGBAMap(width, height)};
        for (int i = 0; i < a.getArea(); i++) {
            image_ret->setPixel(i, a.getPixel(i).rgba());
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Graymap> ImageConverter<Graymap, ImageConversionParam::AVERAGE>::convert(RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Graymap> image_ret{new Graymap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);
            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret->setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Graymap> ImageConverter<Graymap, ImageConversionParam::LUMINOSITY>::convert(RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Graymap> image_ret{new Graymap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);
            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret->setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Graymap> ImageConverter<Graymap, ImageConversionParam::AVERAGE>::convert(RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Graymap> image_ret{new Graymap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);
            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret->setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Graymap> ImageConverter<Graymap, ImageConversionParam::LUMINOSITY>::convert(RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Graymap> image_ret{new Graymap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);
            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret->setPixel(i, avg);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<RGBMap> ImageConverter<RGBMap>::convert(Graymap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<RGBMap> image_ret{new RGBMap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i);
            image_ret->setPixel(i, RGB(temp, temp, temp));
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<RGBAMap> ImageConverter<RGBAMap>::convert(Graymap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<RGBAMap> image_ret{new RGBAMap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i);
            image_ret->setPixel(i, RGBA(temp, temp, temp, 255));
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<RGBAMap> ImageConverter<RGBAMap>::convert(Bitmap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<RGBAMap> image_ret{new RGBAMap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i) ? 255 : 0;
            image_ret->setPixel(i, RGBA(temp, temp, temp, 255));
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<RGBMap> ImageConverter<RGBMap>::convert(Bitmap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<RGBMap> image_ret{new RGBMap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i) ? 255 : 0;
            image_ret->setPixel(i, RGB(temp, temp, temp));
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Graymap> ImageConverter<Graymap>::convert(Bitmap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Graymap> image_ret{new Graymap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i) ? 255 : 0;
            image_ret->setPixel(i, temp);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Bitmap> ImageConverter<Bitmap, ImageConversionParam::AVERAGE>::convert(RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Bitmap> image_ret{new Bitmap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);

            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret->setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Bitmap> ImageConverter<Bitmap, ImageConversionParam::LUMINOSITY>::convert(RGBMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Bitmap> image_ret{new Bitmap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGB temp = a.getPixel(i);

            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret->setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Bitmap> ImageConverter<Bitmap, ImageConversionParam::AVERAGE>::convert(RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Bitmap> image_ret{new Bitmap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);

            int avg = temp.r / 3.0 + temp.g / 3.0 + temp.b / 3.0;
            image_ret->setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Bitmap> ImageConverter<Bitmap, ImageConversionParam::LUMINOSITY>::convert(RGBAMap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Bitmap> image_ret{new Bitmap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            RGBA temp = a.getPixel(i);

            int avg = 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b;
            image_ret->setPixel(i, avg > 128);
        }

        return image_ret;
    }

    template<>
    std::unique_ptr<Bitmap> ImageConverter<Bitmap>::convert(Graymap &a) {
        int width = a.getWidth();
        int height = a.getHeight();

        std::unique_ptr<Bitmap> image_ret{new Bitmap(width, height)};
        for (size_t i = 0; i < a.getArea(); i++) {
            int temp = a.getPixel(i);
            image_ret->setPixel(i, temp > 128);
        }

        return image_ret;
    }

}

#endif
