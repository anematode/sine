#ifndef PIXMAP_DEFINED_
#define PIXMAP_DEFINED_

#include <string>

#include <algorithm>
#include <exception>
#include <iostream>

#include "../math/vec2.h"
#include "imageutils.h"
#include "color.h"
#include <fstream>

#include "stb_image_write.h"

#include <cmath>
#include <functional>

namespace Sine {

    /**
  Pixmap is the base class for Graymap, Bitmap, RGBMap and RGBMap
  Basically it just abstracts a 2D array of pixels, given a template argument for the pixel itself
    **/


    namespace PixmapApply {
        const unsigned char NORETURN = 0,
                RETURN = 1,
                NOPASSINDEX = 0,
                PASSINDEX = (1 << 1),
                NOPASSPAIR = 0,
                PASSPAIR = (1 << 2);
    };

    template<typename F, typename Ret, typename... Rest>
    Ret helper_get_return_type(Ret (F::*)(Rest...));

    template<typename F, typename Ret, typename... Rest>
    Ret helper_get_return_type(Ret (F::*)(Rest...) const);

    template<typename F, typename Ret, typename... Rest>
    constexpr size_t helper_get_arg_count(Ret (F::*)(Rest...)) {
        return sizeof...(Rest);
    };

    template<typename F, typename Ret, typename... Rest>
    constexpr size_t helper_get_arg_count(Ret (F::*)(Rest...) const) {
        return sizeof...(Rest);
    };

    template<typename F>
    struct get_functor_traits {
        typedef decltype(helper_get_return_type(&F::operator())) return_type;
        static const size_t arg_count = helper_get_arg_count(&F::operator());
    };

    template<typename PixelColor>
    class Pixmap {
    protected:
        PixelColor *pixels;
        int width;
        int height;
        long area;

    public:
        using PixelType = PixelColor;
        const static int ColorSize = sizeof(PixelColor);

        Pixmap(int width, int height);

        Pixmap(const Pixmap<PixelColor> &p);

        Pixmap(Pixmap<PixelColor> &&p) noexcept;

        Pixmap<PixelColor> &operator=(Pixmap<PixelColor> &&p) noexcept;

        void copyFrom(const Pixmap &p);

        PixelColor *begin();

        PixelColor *end();

        ~Pixmap();

        void checkIndex(int index) const;

        void checkPair(int x, int y) const;

        int getWidth() const;

        int getHeight() const;

        PixelColor *getPixels() const;

        long getArea() const;

        void setPixelPointer(void *p);

        bool indexContained(int index) const;

        bool pairContained(int x, int y) const;

        int pairToIndex(int x, int y) const;

        PixelColor &operator()(int row, int col);

        PixelColor operator()(int row, int col) const;

        PixelColor &operator()(int index);

        PixelColor operator()(int index) const;

        PixelColor getPixel(int index) const;

        PixelColor getPixel(int x, int y) const;

        PixelColor &getPixelRef(int index);

        PixelColor &getPixelRef(int x, int y);

        void setPixel(int index, PixelColor c);

        void setPixel(int x, int y, PixelColor c);

        PixelColor getPixelUnsafe(int index) const;

        PixelColor getPixelUnsafe(int x, int y) const;

        PixelColor &getPixelRefUnsafe(int index);

        PixelColor &getPixelRefUnsafe(int x, int y);

        void setPixelUnsafe(int index, PixelColor c);

        void setPixelUnsafe(int x, int y, PixelColor c);

        bool exportToFile(std::string file,
                          ImageType type = ImageType::UNKNOWN);

        Pixmap sample(double x) const;

        void exportToBMP(std::string file);

        void exportToJPEG(std::string file, int quality = 90);

        void exportToGIF(std::string file);

        void exportToPNG(std::string file);

        void exportToPBM(std::string file);

        void exportToPPM(std::string file);

        void exportToPGM(std::string file);

        template<typename T, unsigned char app = PixmapApply::NORETURN>
        inline void _apply(T func) {
            using namespace PixmapApply;

            if constexpr (app == (NORETURN | NOPASSINDEX | NOPASSPAIR)) {
                for (auto &i : *this) {
                    func(i);
                }
            } else if constexpr ((app == (NORETURN | NOPASSINDEX | PASSPAIR)) ||
                                 (app == (NORETURN | PASSINDEX | PASSPAIR))) {
                int index = 0;
                for (int j = 0; j < height; j++) {
                    for (int i = 0; i < width; i++) {
                        func(getPixelRefUnsafe(index), i, j);
                        index++;
                    }
                } //
            } else if constexpr (app == (NORETURN | PASSINDEX | NOPASSPAIR)) {
                for (int i = 0; i < area; i++) {
                    func(getPixelRefUnsafe(i), i);
                }
            } else if constexpr (app == (RETURN | NOPASSINDEX | NOPASSPAIR)) {
                for (auto &i : *this) {
                    i = func(i);
                }
            } else if constexpr ((app == (RETURN | NOPASSINDEX | PASSPAIR)) ||
                                 (app == (RETURN | PASSINDEX | PASSPAIR))) {
                int index = 0;

                for (int j = 0; j < height; j++) {
                    for (int i = 0; i < width; i++) {
                        setPixelUnsafe(index, func(getPixelUnsafe(index), i, j));
                        index++;
                    }
                }
            } else if constexpr (app == (RETURN | PASSINDEX | NOPASSPAIR)) {
                for (int i = 0; i < area; i++) {
                    setPixelUnsafe(i, func(getPixelUnsafe(i), i));
                }
            }
        }

        template<typename T>
        inline void apply(T func) {
            _apply_l<T>(func);
        }

        template<typename T, typename = typename std::enable_if<std::is_same<typename get_functor_traits<T>::return_type, PixelColor>::value>::type>
        inline void _apply_l(T func, int = 0) {

            _apply_a<T, PixmapApply::RETURN>(func);
        };

        template<typename T, typename = typename std::enable_if<!std::is_same<typename get_functor_traits<T>::return_type, PixelColor>::value>::type>
        inline void _apply_l(T func, double = 0) {

            _apply_a<T, PixmapApply::NORETURN>(func);
        };

        template<typename T, unsigned char opts, typename = typename std::enable_if<
                get_functor_traits<T>::arg_count == 1>::type>
        inline void _apply_a(T func, int = 0) {
            _apply<T, opts>(func);
        };

        template<typename T, unsigned char opts, typename = typename std::enable_if<
                get_functor_traits<T>::arg_count == 2>::type>
        inline void _apply_a(T func, double = 0) {
            _apply<T, opts | PixmapApply::PASSINDEX>(func);
        };

        template<typename T, unsigned char opts, typename = typename std::enable_if<
                get_functor_traits<T>::arg_count == 3>::type>
        inline void _apply_a(T func, long = 0) {
            _apply<T, opts | PixmapApply::PASSPAIR>(func);
        };
    };


    typedef Pixmap<bool> Bitmap;
    typedef Pixmap<RGB> RGBMap;
    typedef Pixmap<uint8_t> Graymap;
    typedef Pixmap<RGBA> RGBAMap;

} // namespace Sine


#endif
